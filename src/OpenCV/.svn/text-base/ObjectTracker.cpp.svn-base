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


#include "ObjectTracker.h"

namespace OpenCV {

namespace Tracking {
    
ObjectTracker::ObjectTracker()
    : MeanShift()
    , m_trackingObject(NULL)
{
}
    
ObjectTracker::ObjectTracker(const ObjectTracker& ot)
    : MeanShift(ot)
    , m_trackingObject(ot.m_trackingObject)
{
}
    
ObjectTracker::ObjectTracker(Image* image, CvRect rect)
    : MeanShift(image, rect)
    , m_trackingObject(NULL)
{
    Mask* mask = m_trackingHist->calcBackProjection(image);
    OpticalObjects* objects = OpticalObject::opticalObjectsFromImage(mask, MIN_PERIMETER_TO_TRACK, ChainApproxSimple);
    delete mask;
    
    for (OpticalObjects::iterator it = objects->begin(); it != objects->end(); it++) {
        OpticalObject* object = (OpticalObject*)(*it);
        if (object->isOnRect(rect)) {
            if (m_trackingObject)   //More than one object
                if (m_trackingObject->distanceTo(rect) < object->distanceTo(rect)) //Choose nearest
                    delete object;
                else {
                    delete m_trackingObject;
                    m_trackingObject = object;
                }
            else
                m_trackingObject = object;
        } else
            delete object; // No longer used
    }
}
    
ObjectTracker::ObjectTracker(Image* image, CvConnectedComp* cComp)
    : MeanShift(image, cComp)
    , m_trackingObject(new OpticalObject(cComp))
{
}
    
ObjectTracker::ObjectTracker(Image* image, OpticalObject* object)
    : MeanShift(image, object->connectedComponents())
    , m_trackingObject(object)
{
}
    
ObjectTracker::ObjectTracker(Histogram* histogram, OpticalObject* object)
    : MeanShift(histogram, object->rect())
    , m_trackingObject(object)
{
}

ObjectTracker::~ObjectTracker()
{
    delete m_trackingObject;
}

void ObjectTracker::setTrackingHistogram(Histogram* histogram)
{
    delete m_trackingHist;
    m_trackingHist = histogram;
}
    
void ObjectTracker::setOpticalObject(OpticalObject* object)
{
    delete m_trackingObject;
    m_trackingObject = object;
}

void ObjectTracker::startTracking(Image* image, CvConnectedComp* cComp)
{
    MeanShift::startTracking(image, cComp);
    delete m_trackingObject;
    m_trackingObject = new OpticalObject(cComp);
}
    
void ObjectTracker::startTracking(Image* image, OpticalObject* oObj)
{
    MeanShift::startTracking(image, oObj->connectedComponents());
    delete m_trackingObject;
    m_trackingObject = oObj;
}
    
OpticalObject* ObjectTracker::trackObject(const Image* image, const Mask* probabilisticMask)
{
    if (!m_trackingObject)
        return NULL;
    
    Mask* mask = m_trackingHist->calcBackProjection(image);

    if (probabilisticMask)
        (*mask) &= (*probabilisticMask);

    OpticalObjects* objects = OpticalObject::opticalObjectsFromImage(mask, MIN_PERIMETER_TO_TRACK, ChainApproxSimple);
    delete mask;

    OpticalObject* newObject = NULL;
    double betterProbability = MIN_PROBABILITY;
    foreach (ptrObject, (*objects)) {
        OpticalObject* object = (OpticalObject*)(*ptrObject);
        double objectProbability = probabilityOfNewPosition(m_trackingObject->rect(), object->rect());
        if (objectProbability >= betterProbability) {
            newObject = object;
            betterProbability = objectProbability;
        } else
            delete object;
        
    }
    
    if (newObject) {
        delete m_trackingObject;
        return m_trackingObject = newObject;
    }
    return m_trackingObject;
}

#define CV_RECT_CENTER_X(r)     (r.x + (r.width / 2))
#define CV_RECT_CENTER_Y(r)     (r.y + (r.height / 2))
#define CV_RECT_DISTANCE(r0, r1)    sqrt(pow(abs(CV_RECT_CENTER_X(r0) - CV_RECT_CENTER_X(r1)), 2) + \
                                         pow(abs(CV_RECT_CENTER_Y(r0) - CV_RECT_CENTER_Y(r1)), 2))
    
double ObjectTracker::probabilityOfNewPosition(CvRect oldRect, CvRect newRect)
{
    double offset, areaOffset;
    offset = 1 / (1 + (CV_RECT_DISTANCE(oldRect, newRect) / 128));
    areaOffset = 1 / (1);
    return offset * areaOffset;
}
    
} // namespace Tracking
    
} // namespace OpenCV

