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


#include "OFLKTracker.h"

namespace OpenCV {
    
namespace Tracking {
    
OFLKTracker::OFLKTracker(const OFLKTracker& oflkTracker)
    : m_oflk(oflkTracker.m_oflk)
    , m_lastPosition(oflkTracker.m_lastPosition)
{
}
    
OFLKTracker::OFLKTracker(const Image* image, const CvConnectedComp* cc)
    : m_oflk(NULL)
{
    startTracking(image, cc);
}
    
OFLKTracker::OFLKTracker(const Image* image, CvRect rect, const Mask* mask)
    : m_oflk(NULL)
{
    startTracking(image, rect, mask);
}
    
OFLKTracker::~OFLKTracker()
{
    delete m_oflk;
}

void OFLKTracker::startTracking(const Image* image, const CvConnectedComp* cComp)
{
    if (!cComp->contour)
        return startTracking(image, cComp->rect);
    
    Image* mask = new Image(image->size(), UByte, 1);
    cvDrawContours(mask->cvImage(),
                   cComp->contour, 
                   cvScalar(255),
                   cvScalar(255), 
                   -1,
                   CV_FILLED,
                   8);

    startTracking(image, cComp->rect, mask);
    delete mask;
}
    
void OFLKTracker::startTracking(const Image* image, CvRect rect, const Mask* mask)
{
    DrawableImage* rectmask = new DrawableImage(image->size(), UByte, 1);
    rectmask->drawBox(rect, cvScalar(255));
    delete m_oflk;
    if (mask)
        (*rectmask) &= (*mask);
    //static_cast<ProcessableImage*> (rectmask)->morphologyEx(Close, 1);
    m_oflk = new OpticalFlowLK(image, rectmask, MAX_POINTS_TO_TRACK);
    m_lastPosition = rect;
    delete rectmask; 
}

CvConnectedComp* OFLKTracker::track(const Image* image, const Mask*)
{
    if (!m_oflk)
        return NULL;
    
    Flow* trackingFlow = m_oflk->calcOpticalFlow(image);
    Vector2D32f v = standardVector(trackingFlow);
    
    CvConnectedComp* cc = new CvConnectedComp;
    
    if ((m_lastPosition.x += v.dx()) < 0) 
        m_lastPosition.x = 0;
    if ((m_lastPosition.y += v.dy()) < 0)  
        m_lastPosition.y = 0;
    cc->rect = m_lastPosition;
    
    DrawableImage* mask = new DrawableImage(image->size(), UByte, 1);
    mask->drawBox(m_lastPosition, cvScalar(255));
    m_oflk->seedImage(image, mask);
    delete mask; 
    
    return cc;
}
    
Vector2D32f OFLKTracker::standardVector(Flow* flow)
{
    Vector2D32f v; 
    if (!flow->size())
        return v;
    
    // calculate average vector
    Vector2D32f av;
    for (unsigned int i = 0; i < flow->size(); i++)
        av += (*flow)[i];
    av /= flow->size();
    
    // calculate standar desviation
    CvPoint2D32f sdv;
    sdv.x = 0;
    sdv.y = 0;
    
    foreach (vector, (*flow)) {
        sdv.x += (vector->dx() - av.dx()) * (vector->dx() - av.dx());
        sdv.y += (vector->dy() - av.dy()) * (vector->dy() - av.dy());
    }
    sdv.x = sqrt(sdv.x / flow->size());
    sdv.y = sqrt(sdv.y / flow->size());
    
    // filter non standard desviated vectors and background vectors
    int count = 0;
    for (unsigned int i = 0; i < flow->size(); i++)
        if ((abs((*flow)[i].dx() - av.dx()) <= sdv.x) 
            && (abs((*flow)[i].dy() - av.dy()) <= sdv.y) 
            && (abs((*flow)[i].dx()) > BACKGROUNG_VECTOR_LENGHT) 
            && (abs((*flow)[i].dy()) > BACKGROUNG_VECTOR_LENGHT)) {
            v += (*flow)[i];
            count++;
        }
    
    if (count)
        v /= count;

    return v;
}

} // namespace Tracking
    
} //namespace OpenCV
