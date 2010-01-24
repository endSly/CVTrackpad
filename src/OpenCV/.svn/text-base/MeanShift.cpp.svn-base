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


#include "MeanShift.h"

namespace OpenCV {
    
namespace Tracking {

MeanShift::MeanShift()
{
}
    
MeanShift::MeanShift(const MeanShift& ms)
    : m_trackingHist(ms.m_trackingHist->copy())
    , m_lastPostition(ms.m_lastPostition)
    , m_components(ms.m_components)
{
}

MeanShift::MeanShift(const Image* image, const CvConnectedComp* cComp)
    : m_trackingHist(NULL)
{
    startTracking(image, cComp);
}

MeanShift::MeanShift(const Image* image, CvRect rect)
    : m_trackingHist(NULL)
{
    startTracking(image, rect);
}

MeanShift::MeanShift(const Histogram* hist, CvRect lastPos)
    : m_trackingHist(hist->copy())
    , m_lastPostition(lastPos)
{
}

MeanShift::~MeanShift()
{
    delete m_trackingHist;
}

void MeanShift::startTracking(const Image* image, const CvConnectedComp* cComp)
{
    if (!cComp->contour)    /* Not really connected component */
        return startTracking(image, cComp->rect);

    Image* mask = new Image(image->size(), UByte, 1);
    cvDrawContours(mask->cvImage(),
                   cComp->contour,
                   cvScalar(255),
                   cvScalar(255),
                   -1,
                   CV_FILLED,
                   8);

    delete m_trackingHist;
    m_trackingHist = Histogram::createHSHistogram(image, mask);
    m_lastPostition = cComp->rect;
    delete mask;
}

void MeanShift::startTracking(const Image* image, CvRect rect)
{
    DrawableImage* mask = new DrawableImage(image->size(), UByte, 1);
    mask->drawBox(rect, cvScalar(255));
    delete m_trackingHist;
    m_trackingHist = Histogram::createHSHistogram(image, mask);
    m_lastPostition = rect;
    delete mask;
}

void MeanShift::startTracking(const Histogram* hist, CvRect lastPos)
{
    delete m_trackingHist;
    m_trackingHist = hist->copy();
    m_lastPostition = lastPos;
}
    
void MeanShift::setTrackingHistogram(const Histogram* histogram)
{
    delete m_trackingHist;
    m_trackingHist = histogram->copy(); 
}
    
CvConnectedComp* MeanShift::track(const Image* image, const Mask* probabilisticMap)
{
    if (!m_trackingHist || !image)
        return NULL;
    
    //Obtain probabilistic image from backProject of histogram
    Mask* probimage = m_trackingHist->calcBackProjection(image);
    if (probabilisticMap)
        (*probimage) &= (*probabilisticMap);

    if ((m_lastPostition.width < 0) || (m_lastPostition.height < 0)
        || (m_lastPostition.x > image->width()) || (m_lastPostition.y > image->height()))
        return &m_components;
    
    //cvTermCriteria with CV_TERMCRIT_ITER specifies number of iteratios until center of mass found
    //cvTermCriteria with CV_TERMCRIT_EPS specifies the max error of the result
    cvMeanShift(probimage->cvImage(),
                m_lastPostition,
                cvTermCriteria(CV_TERMCRIT_EPS, 256, .001l),
                &m_components);
    
    //Update lastPosition
    m_lastPostition = m_components.rect;
    
    delete probimage;
    
    return &m_components;
}

} // namespace Tracking
    
} // namespace OpenCV
