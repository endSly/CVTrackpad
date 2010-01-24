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


#include "Histogram.h"

namespace OpenCV {
    
namespace Bitmap {
	
Histogram::Histogram()
        : m_histogram(NULL)
{
}

Histogram::Histogram(int dims,
                     int* sizes,
                     float** ranges,
                     int type,
                     Histogram* histToAcomul)
        : m_histogram(histToAcomul ? histToAcomul->m_histogram : NULL)
{
        m_histogram = cvCreateHist(dims, sizes, type, ranges, histToAcomul ? 0 : 1);
}

Histogram::Histogram(const Histogram& hist)
{
    cvCopyHist(hist.m_histogram, &m_histogram);
}

Histogram::~Histogram()
{
    cvReleaseHist(&m_histogram);
}

Histogram* Histogram::createHSHistogram(const Image* image, const Mask* mask, int sizeH, int sizeS)
{
    Histogram* hist = new Histogram();
    IplImage* hsv = cvCreateImage(image->size(), 8, 3);	//Create HSV image from BGR image
    cvCvtColor(image->cvImage(), hsv, CV_BGR2HSV);
	
    IplImage* h = cvCreateImage(image->size(), 8, 1);	// create diferents planes
    IplImage* s = cvCreateImage(image->size(), 8, 1);
    IplImage* v = cvCreateImage(image->size(), 8, 1);
	
    IplImage* planes[] = {h, s};
	
    cvCvtPixToPlane(hsv, h, s, v, NULL);
	
    int histSize[] = {sizeH, sizeS};
    float hRanges[] = { 0, 180 }; /* hue varies from 0 (~0°red) to 180 (~360°red again) */
    float sRanges[] = { 0, 255 }; /* saturation varies from 0 (black-gray-white) to 255 (pure spectrum color) */
    float* ranges[] = {hRanges, sRanges};
	
    hist->m_histogram = cvCreateHist(2, histSize, CV_HIST_ARRAY, ranges, 1);
    cvCalcHist(planes, hist->m_histogram, false, mask ? mask->cvImage() : NULL);

    cvReleaseImage(&hsv);
    cvReleaseImage(&h);
    cvReleaseImage(&s);
    cvReleaseImage(&v);
    return hist;
}
	
Histogram* Histogram::createRGBHistogram(const Image* image, const Mask* mask)
{
	Histogram* hist = new Histogram();
	
	IplImage* r = cvCreateImage(image->size(), 8, 1);	// create color channels
	IplImage* g = cvCreateImage(image->size(), 8, 1);
	IplImage* b = cvCreateImage(image->size(), 8, 1);
	
	IplImage* rgb[] = {r, g, b};
	
	cvSplit(image->cvImage(), r, g, b, NULL);
	int histSize[] = {256, 256, 256};
	float range[] = { 0, 255 }; 
	float* ranges[] = {range, range, range};
	
	hist->m_histogram = cvCreateHist(3, histSize, CV_HIST_ARRAY, ranges, 1);
	cvCalcHist(rgb, hist->m_histogram, false, mask ? mask->cvImage() : NULL);
        cvReleaseImage(&r);
        cvReleaseImage(&g);
        cvReleaseImage(&b);
	return hist;
}
	
Histogram* Histogram::create1ChHistogram(const Image* image, const Mask* mask)
{
    Histogram* hist = new Histogram();
	
    int histSize[] = {256};
    float range[] = { 0, 255 };
    float* ranges[] = {range};
    IplImage* cvimage = image->cvImage();
	
    hist->m_histogram = cvCreateHist(1, histSize, CV_HIST_ARRAY, ranges, 1);
    cvCalcHist(&cvimage , hist->m_histogram, false, mask ? mask->cvImage() : NULL);
    hist->normalize();
	
    return hist;
}
	
Image* Histogram::equalizeHist(const Image* image)
{
        Image* equalizedImage = image->clone();
        cvEqualizeHist(image->cvImage(), equalizedImage->cvImage());
        return equalizedImage;
}

#ifdef DEBUG
	
Mask* Histogram::representInMask()
{
	int h_bins = 30, s_bins = 32; 
	int scale = 10;
	IplImage* hist_image = cvCreateImage(cvSize( h_bins * scale, s_bins * scale ), 
                                         8, 
                                         3); 
	cvZero( hist_image );
	
	/* populate our visualization with little gray squares. */
	float max_value = 0;
	cvGetMinMaxHistValue( m_histogram, 0, &max_value, 0, 0 );
	
	for( int h = 0; h < h_bins; h++ ) {
		for( int s = 0; s < s_bins; s++ ) {
			float bin_val = cvQueryHistValue_2D( m_histogram, h, s );
			int intensity = cvRound( bin_val * 255 / max_value );
			cvRectangle(hist_image, 
                                    cvPoint( h*scale, s*scale ),
                                    cvPoint( (h+1)*scale - 1, (s+1)*scale - 1),
                                    CV_RGB(intensity,intensity,intensity),
                                    CV_FILLED);
		}
	}
	
	return new Image(hist_image);
}
	
#endif // DEBUG
	
Histogram* Histogram::copy() const
{
	Histogram* hist = new Histogram();
	cvCopyHist(m_histogram, &(hist->m_histogram));
	return hist;
}

float Histogram::min() const
{
	float min, max;
	cvGetMinMaxHistValue(m_histogram, &min, &max);
	return min;
}
	
float Histogram::max() const
{
	float min, max;
	cvGetMinMaxHistValue(m_histogram, &min, &max);
	return max;
}
	
float Histogram::getValue(int idx0, int idx1, int idx2) const
{
	switch (m_histogram->mat.dims) {
		case 1:
			return *cvGetHistValue_1D(m_histogram, idx0);
		case 2:
			return *cvGetHistValue_2D(m_histogram, idx0, idx1);
		case 3:
			return *cvGetHistValue_3D(m_histogram, idx0, idx1, idx2);
	}
	return NULL;
	
}
    
float Histogram::calcEMD2(const Histogram* histogram1, const Histogram* histogram2, int distanceType)
{
    Signature* signature1 = histogram1->signature();
    Signature* signature2 = histogram2->signature();
    
    float emd2 = cvCalcEMD2(signature1, signature2, distanceType);
    
    cvRelease(&signature1);
    cvRelease(&signature2);
    
    return emd2;
}
   
Mask* Histogram::calcBackProjection(const Image* rgbImage) const
{
    if (!m_histogram || !rgbImage)
        return NULL;
    if (!(rgbImage->cvImage()))
        return NULL;
    
    IplImage* hsv = cvCreateImage(rgbImage->size(), 8, 3);	//Create HSV image from BGR image
    cvCvtColor(rgbImage->cvImage(), hsv, CV_BGR2HSV);
	
    IplImage* h = cvCreateImage(rgbImage->size(), 8, 1);	// create diferents planes
    IplImage* s = cvCreateImage(rgbImage->size(), 8, 1);
    IplImage* v = cvCreateImage(rgbImage->size(), 8, 1);
	
    IplImage* planes[] = {h, s};
	
    cvCvtPixToPlane(hsv, h, s, v, NULL);
	
    IplImage* backProject = cvCreateImage(rgbImage->size(), 8, 1);
	
    cvCalcBackProject(planes, backProject, m_histogram);
	
    cvReleaseImage(&hsv);
    cvReleaseImage(&h);
    cvReleaseImage(&s);
    cvReleaseImage(&v);
	
    return new Image(backProject);
}
	
Mask* Histogram::calcPatchBackProjection(const Image*, CvSize, float, int) const
{
	throw "NotImplementedExcepetion";
}
	
void Histogram::normalize(double factor)
{
	cvNormalizeHist(m_histogram, factor);
}
    
Signature* Histogram::createSignature(const Histogram* histogram)
{
    int hSize = histogram->dimensionSize(0), sSize = histogram->dimensionSize(1);
    int rowsCount = hSize * sSize;  //get size
    
    if (!rowsCount)
        return NULL;    // Only works with 2D (or more) histograms
    
    Signature* signature = cvCreateMat(rowsCount, 3, CV_32FC1);     //Signature is a Mat
    
    /* Set values for signature */
    for (int h = hSize; h-- /* NOT --h */; )      // We supouse that it's HSV histogram
        for (int s = sSize; s-- /* NOT --s */; ) {
            float value = cvQueryHistValue_2D(histogram->m_histogram, h, s);
            cvSet2D(signature, h * sSize + s, 0, cvScalar(value));
            cvSet2D(signature, h * sSize + s, 1, cvScalar(h));
            cvSet2D(signature, h * sSize + s, 2, cvScalar(s));
        }
    return signature;
}
    
} // namespace Bitmap
	
} // namespace OpenCV
