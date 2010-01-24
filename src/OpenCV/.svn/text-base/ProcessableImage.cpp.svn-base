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


#include "ProcessableImage.h"

namespace OpenCV {
    
namespace Bitmap {
	
ProcessableImage::ProcessableImage()
	: Image()
{
}
	
ProcessableImage::ProcessableImage(const ProcessableImage& image)
	: Image(image)
{
}
    
ProcessableImage::ProcessableImage(const Image& image)
    : Image(image)
{
}
	
ProcessableImage::ProcessableImage(CvSize size, int depth, int channels)
	: Image(size, depth, channels)
{
}
	
ProcessableImage::~ProcessableImage()
{
    if (m_image)
        cvReleaseImage(&m_image);
}

void ProcessableImage::threshold(double val, double max, int type)
{
    cvThreshold(m_image, m_image, val, max, type);
}
    
void ProcessableImage::adaptiveThreshold(double max, int method, int type, int blockSize)
{
    cvAdaptiveThreshold(m_image, m_image, max, method, type, blockSize);
}
    
	
Image* ProcessableImage::warpPerspective(CvPoint2D32f* currentCorners, CvPoint2D32f* newCorners)
{
	CvMat* warpMat = cvCreateMat(3, 3, CV_32FC1);	//Create new matrix for transformation
	if (!newCorners) {
		newCorners = new CvPoint2D32f[4];		//Set newCorners to corners of image
		newCorners[0].x = 0;				//Top left
		newCorners[0].y = 0;
		newCorners[1].x = size().width - 1;	//Top rigth
		newCorners[1].y = 0;
		newCorners[2].x = 0;				//Bottom left
		newCorners[2].y = size().height - 1;
		newCorners[3].x = size().width - 1;	//Bottom rigth
		newCorners[3].y = size().height - 1;
	}
	cvGetPerspectiveTransform(currentCorners, newCorners, warpMat);	//generate transformation matrix
	Image* warpedImage = warpPerspective(warpMat);	//New image with warped image
	cvReleaseMat(&warpMat);	//Relese matrix
	return warpedImage;
}
    
void ProcessableImage::morphologyEx(int operation, int iterations)
{
    Image* tempImage = NULL;
    if (operation != Open && operation != Close) //Not needed temporal image
        this->clone();
        
    cvMorphologyEx(m_image, m_image, tempImage, NULL, operation, iterations);
}
	
	
CvPoint2D32f* ProcessableImage::findChessboardCorners(int rows, int columns, int flags)
{
	int cornersCount = rows * columns;
	CvPoint2D32f* corners = new CvPoint2D32f[cornersCount];
    Image* grayImage = m_image->nChannels > 1 ? Image::convert(this, CV_RGB2GRAY) : this;
	cvFindChessboardCorners(grayImage, cvSize(rows, columns), corners, &cornersCount, flags);
    if (m_image->nChannels > 1)
        delete grayImage;
	return corners;
}
	
IplImage* ProcessableImage::convert(int flags)
{
	IplImage* image2 = cvCreateImage(size(), depth(), 1);
	cvConvertImage(m_image, image2, flags);
	return image2;
}
	
Image* ProcessableImage::warpPerspective(CvMat* warpMat)
{
	IplImage* warpedImage = cvCloneImage(m_image);
        cvWarpPerspective(m_image, warpedImage, warpMat);
	return new Image(warpedImage);
}
    
} // namespace Bitmap
	
} // namespace OpenCV
