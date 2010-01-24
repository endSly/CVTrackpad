/*-
 * Copyright (c) 2009 Ander Suarez and Endika Gutiérrez
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of copyright holders nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include "Hand.h"

namespace HumanInterface {

 /* class HandServer */

HandServer::HandServer(const HandServer& hs)
    : m_faceClassifier(hs.m_faceClassifier)
    , m_handHistogram(hs.m_handHistogram)
    , m_faceSkinHistogram(NULL)
{
}

HandServer::HandServer(HaarClassifier* hc)
    : m_faceClassifier(hc)
    , m_handHistogram(NULL)
    , m_faceSkinHistogram(NULL)
{
}

HandServer::HandServer(Histogram* histogram)
    : m_faceClassifier(NULL)
    , m_handHistogram(histogram)
    , m_faceSkinHistogram(NULL)
    , m_faceRect(CV_RECT_ZERO)
{
}

HandServer::~HandServer()
{
    delete m_faceClassifier;
}

vector<Hand*>* HandServer::findAllHands(const Image* image, const Mask* probabilisticMap)
{
    Mask* handProbabilisticMap = handsProbabilisticMap(image);
    if (!handProbabilisticMap)
        return new vector<Hand*>(0);

    if (probabilisticMap)   // Apply probabilistic map
        (*handProbabilisticMap) &= (*probabilisticMap);

    vector<OpticalObject*>* handObjects = OpticalObject::opticalObjectsFromImage(handProbabilisticMap);
    if (!evaluateFoundObjects(*handObjects, image))  // Evaluate only valid objects
        return new vector<Hand*>(0);    // No objects found

    // Convert Optical Objects to Hands
    vector<Hand*>* foundHands = new vector<Hand*>(handObjects->size() > MAX_HANDS_TO_TRACK
                                                                        ? MAX_HANDS_TO_TRACK
                                                                        : handObjects->size());
    for (int i = 0
         ; i < foundHands->size() && (*handObjects)[i]
         ; i++)
        (*foundHands)[i] = new Hand((*handObjects)[i]);

    // Delete unused objects
    for (int i = MAX_HANDS_TO_TRACK; i < handObjects->size(); i++)
        delete (*handObjects)[i];

    delete handObjects;
    return foundHands;
}

Mask* HandServer::handsProbabilisticMap(const Image* image)
{
    Mask* handProbabilisticMap = NULL;
    if (m_faceClassifier) {
        findFace(image);
        if (!m_faceSkinHistogram) // There are nothing to find hand
            return NULL;
        handProbabilisticMap = m_faceSkinHistogram->calcBackProjection(image);
        // Exclude also neck
        CvRect headRect = cvRect(m_faceRect.x, m_faceRect.y, m_faceRect.width, (int)((float)m_faceRect.height * 1.2f));
        static_cast<DrawableImage*> (handProbabilisticMap)->drawBox(headRect, COLOR_BLACK);

    } else /* m_handHistogram */
        handProbabilisticMap = m_handHistogram->calcBackProjection(image);

    return handProbabilisticMap;
}

void HandServer::findFace(const Image* image)
{
    assert(m_faceClassifier && image); //We need image

    vector<CvRect>* foundFaces = m_faceClassifier->findObjects(image);
    if (!foundFaces->size()) {  // if no face found
        delete foundFaces;      // Do nothing
        return;
    }

    // Now we have face, update histogram
    CvRect rect = cvRect((*foundFaces)[0].x + (*foundFaces)[0].width / 8,  // Exclude face borders
                         (*foundFaces)[0].y + (*foundFaces)[0].height / 8, // for better performance
                         (*foundFaces)[0].width * 3 / 4,
                         (*foundFaces)[0].height * 3 / 4);

    // First obtain Histogram
    delete m_faceSkinHistogram;
    DrawableImage* mask = new DrawableImage(image->size(), UByte, 1);   // Create mask for histogram
    mask->drawBox(rect, COLOR_WHITE);
    m_faceSkinHistogram = Histogram::createHSHistogram(image, static_cast<Mask*> (mask));
    delete mask;

    m_faceRect = (*foundFaces)[0];
}

int HandServer::evaluateFoundObjects(vector<OpticalObject*>& foundObjects, const Image* image)
{
    map<double, OpticalObject*> valuatedObjects;
    for (int i = 0; i < foundObjects.size() && foundObjects[i]; i++) {
        /*
         * Check Rect's size and location
         */
        if ((m_faceClassifier && foundObjects[i]->isOnRect(m_faceRect))  //if We have to exclude
            || (foundObjects[i]->area() < (m_faceClassifier                //or too small objects
                                           ? (m_faceRect.width * m_faceRect.height / 4)
                                           : (MINIMUM_PERIMETER / 4) * (MINIMUM_PERIMETER / 4)))
            || (foundObjects[i]->area() > (m_faceClassifier                //or too small objects
                                           ? (m_faceRect.width * m_faceRect.height * 2)
                                           : MINIMUM_PERIMETER * MINIMUM_PERIMETER * 2))) {
            delete foundObjects[i];   // skip object
            foundObjects.erase(foundObjects.begin() + i);
            i--;    // Do not skip next object
            continue;
        }

        /*
         * Check Object's color and arrange it
         */
        DrawableImage* mask = new DrawableImage(image->size(), UByte, 1);   // Create mask for histogram
        mask->drawObject(foundObjects[i], COLOR_WHITE);
        Histogram* objectHistogram = Histogram::createHSHistogram(image, mask);
        delete mask;

        double correlationValue = objectHistogram->compare(m_faceSkinHistogram, Correlation); //Get the correlation value
        delete objectHistogram;
        if (correlationValue < CORRELATION_THRESHOLD) {     // Bad color correlation
            delete foundObjects[i];   // skip object
            foundObjects.erase(foundObjects.begin() + i);
            i--;    // Do not skip next object
            continue;
        }
        // Map sorts objects automaticaly
        valuatedObjects[correlationValue] = foundObjects[i];
    }


    /*
     * Check if it was after in historial
     */


     /*  Save changes to vector */
    int i = 0;
    foundObjects.resize(valuatedObjects.size());
    for (map<double, OpticalObject*>::iterator it = valuatedObjects.begin(); it != valuatedObjects.end(); it++) {
        foundObjects[i++] = it->second;
    }
    assert(i == foundObjects.size());

    return i;
}

void HandServer::updateHistorial(const vector<Hand*>& hands)
{
    static long time = clock();
    foreach (hand, hands) {
        HandPositionEntry* foundEntry = NULL;
        foreach (histEntry, m_handsHistorial)   // find if it was previusly in hand's historial
            if ((*hand)->isOnRect(histEntry->lastPosition)) {
                foundEntry = &(*histEntry);
                break;
            }
        if (foundEntry) {
            // Update entry
            foundEntry->lastPosition = (*hand)->rect();
            foundEntry->lastArea = (*hand)->area();
            foundEntry->lastTimeTracked = clock();
            foundEntry->timeTracked += (clock() - time);
        } else {
            // Create new entry
            HandPositionEntry newEntry;
            newEntry.lastPosition = (*hand)->rect();
            newEntry.lastArea = (*hand)->area();
            newEntry.lastTimeTracked = clock();
            newEntry.timeTracked = (clock() - time);
            m_handsHistorial.push_back(newEntry);
        }
    }
}

/* class Hand */

Hand::Hand(const OpticalObject* optObj, const Image* image)
    : OpticalObject(*optObj)
    , m_skinColor(NULL)
{
    if (!image)
        return;
    DrawableImage* mask = new DrawableImage(image->size(), UByte, 1);
    mask->drawObject(optObj, COLOR_WHITE);
    m_skinColor = Histogram::createHSHistogram(image, static_cast<Mask*> (mask));
    delete mask;
}

Hand::Hand(const OpticalObject* optObj, Histogram* histogram)
    : OpticalObject(*optObj)
    , m_skinColor(histogram)
{

}

Hand::~Hand()
{
    delete m_skinColor;
}

} // namespace HumanInterface
