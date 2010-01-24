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


#include "HaarClassifier.h"

namespace OpenCV {

namespace MachineLearning {

HaarClassifier::HaarClassifier()
    : m_classifier(NULL)
    , m_storage(cvCreateMemStorage(0))
{
}
    
HaarClassifier::HaarClassifier(const char* filename) 
    throw (FileNotFoundException)
    : m_classifier((CvHaarClassifierCascade*)cvLoad(filename, 0, 0, 0))
    , m_storage(cvCreateMemStorage(0))
{
    if (!m_classifier)
        throw FileNotFoundException(filename);
}
    
HaarClassifier::HaarClassifier(const HaarClassifier& hc)
    : m_classifier(hc.m_classifier)
    , m_storage(cvCreateMemStorage(0))  /* each have their own memory storage */
{
}
    
HaarClassifier::~HaarClassifier()
{
    cvReleaseHaarClassifierCascade(&m_classifier);
    cvReleaseMemStorage(&m_storage);
}
    
void HaarClassifier::loadClassifier(const char* filename) 
    throw (FileNotFoundException)
{ 
    if (m_classifier)
        cvReleaseHaarClassifierCascade(&m_classifier);
    
    m_classifier = (CvHaarClassifierCascade*)cvLoad(filename, 0, 0, 0); 
    if (!m_classifier)
        throw FileNotFoundException(filename);
}
    
FoundObjects* HaarClassifier::findObjects(const Image* image, double scaleFactor, int minNeightbors, int flags, CvSize minSize) const
{
    if (!m_classifier)
        return NULL;
    
    //cvClearMemStorage(m_storage);
    
    //HaarClassifiers works with black and white images
    Image* bwimage;
    if (image->numberOfChannels() > 1) {
        bwimage = Image::convert(image, CV_BGR2GRAY);
        bwimage->resize(cvSize(HAAR_IMAGE_WIDTH, HAAR_IMAGE_HEIGHT));
    } else
        bwimage = Image::resize(image, cvSize(HAAR_IMAGE_WIDTH, HAAR_IMAGE_HEIGHT));

    //cvHaarDetectObjects found paterns in the image in images and returns a sequence
    CvSeq* foundObjectsSeq = cvHaarDetectObjects(bwimage->cvImage(), m_classifier,
                                                 m_storage, scaleFactor, minNeightbors,
                                                 flags, minSize);
    
    delete bwimage;
    
    //Create vector with objects
    FoundObjects* fo = new FoundObjects(foundObjectsSeq ? foundObjectsSeq->total : 0);
    
    for (int i = 0; i < (foundObjectsSeq ? foundObjectsSeq->total : 0); i++) {
        CvRect* object = (CvRect*)cvGetSeqElem(foundObjectsSeq, i);
        (*fo)[i] = (cvRect(object->x * ((float)image->width() / HAAR_IMAGE_WIDTH),
                           object->y * ((float)image->height() / HAAR_IMAGE_HEIGHT), 
                           object->width * ((float)image->width() / HAAR_IMAGE_WIDTH), 
                           object->height * ((float)image->height() / HAAR_IMAGE_HEIGHT)));
    }
    
    return fo;
}

} // namespace MachineLearning

} // namespace OpenCV
