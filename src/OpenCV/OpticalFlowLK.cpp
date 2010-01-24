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


#include "OpticalFlowLK.h"

namespace OpenCV {
    
namespace VectorizedGraphics {
   
OpticalFlowLK::OpticalFlowLK(const OpticalFlowLK& oflk)
    : m_lastimage(oflk.m_lastimage->clone())
    , m_maxTrackCount(oflk.m_maxTrackCount)
    , m_trackCount(oflk.m_trackCount)
    , m_pyramidA(cvCreateImage(cvSize (oflk.m_lastimage->cvImage()->width + 8, oflk.m_lastimage->cvImage()->height / 3), IPL_DEPTH_32F, 1))
    , m_pyramidB(cvCreateImage(cvSize (oflk.m_lastimage->cvImage()->width + 8, oflk.m_lastimage->cvImage()->height / 3), IPL_DEPTH_32F, 1))
    , m_eigen(cvCreateImage(oflk.m_lastimage->size(), IPL_DEPTH_32F, 1))
    , m_temp(cvCreateImage(oflk.m_lastimage->size(), IPL_DEPTH_32F, 1))
    , m_featuresA(new CvPoint2D32f[m_maxTrackCount])
    , m_featuresB(new CvPoint2D32f[m_maxTrackCount])
    , m_featuresErrors(new float[m_maxTrackCount])
    , m_qualityLevel(oflk.m_qualityLevel)
    , m_minDistance(oflk.m_minDistance)
    , m_blockSize(oflk.m_blockSize)
    , m_useHarris(oflk.m_useHarris)
    , m_k(oflk.m_k)
{
}
    
    
OpticalFlowLK::OpticalFlowLK(const Image* image,
                             const Mask* mask,
                             int featCount, 
                             double qualityLevel, 
                             double minDistance, 
                             int blockSize, 
                             int useHarris, 
                             double k)
    : m_lastimage(NULL)
    , m_maxTrackCount(featCount)
    , m_trackCount(new int)
    , m_pyramidA(cvCreateImage(cvSize (image->cvImage()->width + 8, image->cvImage()->height / 3), IPL_DEPTH_32F, 1))
    , m_pyramidB(cvCreateImage(cvSize (image->cvImage()->width + 8, image->cvImage()->height / 3), IPL_DEPTH_32F, 1))
    , m_eigen(cvCreateImage(image->size(), IPL_DEPTH_32F, 1))
    , m_temp(cvCreateImage(image->size(), IPL_DEPTH_32F, 1))
    , m_featuresA(new CvPoint2D32f[featCount])
    , m_featuresB(new CvPoint2D32f[featCount])
    , m_featuresErrors(new float[featCount])
    , m_qualityLevel(qualityLevel)
    , m_minDistance(minDistance)
    , m_blockSize(blockSize)
    , m_useHarris(useHarris)
    , m_k(k)
{
    seedImage(image, mask);
}


OpticalFlowLK::~OpticalFlowLK()
{
    if (m_trackCount)
        delete m_trackCount;
    if (m_pyramidA)
        cvReleaseImage(&m_pyramidA);
    if (m_pyramidB)
        cvReleaseImage(&m_pyramidB);
    if (m_eigen)
        cvReleaseImage(&m_eigen);
    if (m_temp)
        cvReleaseImage(&m_temp);
    if (m_featuresA)
        delete m_featuresA;
    if (m_featuresB)
        delete m_featuresB;
    if (m_featuresErrors)
        delete m_featuresErrors;
}
    
void OpticalFlowLK::seedImage(const Image* image, const Mask* mask)
{
    if (m_lastimage)
        delete m_lastimage;
    
    m_lastimage = image->numberOfChannels() > 1 ? Image::convert(image, CV_BGR2GRAY) : image->clone();
    
    *m_trackCount = m_maxTrackCount;
    
    assert(m_lastimage && m_eigen && m_eigen && m_temp && m_featuresB);
    
    //Find good features for tracking
    cvGoodFeaturesToTrack(m_lastimage->cvImage(), 
                          m_eigen, 
                          m_temp,
                          m_featuresA, 
                          m_trackCount, 
                          m_qualityLevel, 
                          m_minDistance, 
                          mask ? mask->cvImage() : NULL, 
                          m_blockSize, 
                          m_useHarris, 
                          m_k);

     
}


Flow* OpticalFlowLK::calcOpticalFlow(const Image* image)
{
    
    char flowFeature[(*m_trackCount)];
    
    const Image* imageBW = (image->numberOfChannels() > 1) ? Image::convert(image, CV_BGR2GRAY) : image;
	
    cvCalcOpticalFlowPyrLK(m_lastimage->cvImage(),
                           imageBW->cvImage(),
                           m_pyramidA,
                           m_pyramidB,
                           m_featuresA,
                           m_featuresB,
                           *m_trackCount,
                           cvSize(10, 10),
                           5, 
                           flowFeature,
                           m_featuresErrors, 
                           cvTermCriteria( EpsilonWithMaxIter, 20, .3 ),
                           0);
	
    Flow* opticFlow = new Flow;
    
    for (int i = 0; (i < *m_trackCount); i++)
    if (flowFeature[i]) {
        Vector2D32f v;
        v.p1 = m_featuresB[i];
        v.p0 = m_featuresA[i];
        opticFlow->push_back(v);
    }

    delete imageBW;
    //delete flowFeature;
    
    return opticFlow;
}
    
} // namespace VectorizedGraphics

} // namespace OpenCV
