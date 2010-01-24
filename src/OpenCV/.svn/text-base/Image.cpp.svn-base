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


#include "Image.h"

namespace OpenCV {
    
namespace Bitmap {

Image::Image()
	: m_image(NULL)
{
}
    
Image::Image(IplImage* image)
	: m_image(image)
{
}
	
Image::Image(const char* imagePath) throw (FileNotFoundException)
    : m_image(cvLoadImage(imagePath))
{
    if (!m_image)
        throw FileNotFoundException(imagePath);
}
	
Image::Image(CvSize size, int depth, int channels)
    : m_image(cvCreateImage(size, depth, channels))
{
#ifndef SKIP_CLEAR
    cvRectangle(m_image, cvPoint(0, 0), cvPoint(size.width -1, size.height - 1),
                cvScalar(0), CV_FILLED, 0, 0);
#endif // SKIP_CLEAR
}
	
Image::Image(const Image& image)
    : m_image(cvCloneImage(image.m_image))
{
}		
    
Image::~Image()
{
    if (m_image)
        cvReleaseImage(&m_image);
}
	
Image* Image::convert(const Image* image, int flags)
{
	IplImage* newImage = cvCreateImage(image->size(), UByte, ((flags == CV_RGB2GRAY) || (flags == CV_BGR2GRAY)) ? 1 : 3 );
	cvCvtColor(image->m_image, newImage, flags);
	return new Image(newImage);
}
	
Image* Image::resize(const Image* image, CvSize newSize, int method)
{
	IplImage* newImage = cvCreateImage(newSize, image->depth(), image->numberOfChannels());
	cvResize(image->m_image, newImage, method);
	return new Image(newImage);
}
	
Image* Image::clone() const
{
	IplImage* newImage = cvCloneImage(m_image);
	return new Image(newImage);
}
	
void Image::convert(int flags)
{
	IplImage* newImage = cvCreateImage(size(), UByte, ((flags == CV_RGB2GRAY) || (flags == CV_BGR2GRAY)) ? 1 : 3 );
	cvConvertImage(m_image, newImage, flags);
    cvReleaseImage(&m_image);
    m_image = newImage;
}
	
void Image::resize(CvSize newSize, int method)
{
	IplImage* newImage = cvCreateImage(newSize, this->depth(), this->numberOfChannels());
	cvResize(m_image, newImage, method);
	cvReleaseImage(&m_image);
	m_image = newImage;
}
	
int Image::operator==(const Image& image)
{
	return (m_image == image.m_image);
}
	
Image& Image::operator=(const Image& image)
{
	m_image = cvCloneImage(image.m_image);
	return *this;
}
	
Image& Image::operator+(const Image& image)
{
	Image * resultimage = new Image(size(), depth(), numberOfChannels());
	cvAdd(m_image, image.m_image, resultimage->m_image, NULL);
	return *resultimage;
}

Image& Image::operator+=(const Image& image)
{
	cvAdd(m_image, image.m_image, m_image, NULL);
	return *this;
}
	
Image& Image::operator-(const Image& image)
{
	Image * resultimage = new Image(size(), depth(), numberOfChannels());
	cvSub(m_image, image.m_image, resultimage->m_image, NULL);
	return *resultimage;
}
	
Image& Image::operator-=(const Image& image)
{
	cvSub(m_image, image.m_image, m_image, NULL);
	return *this;
}
	
Image& Image::operator*(const Image& image)
{
	Image * resultimage = new Image(size(), depth(), numberOfChannels());
	cvMul(m_image, image.m_image, resultimage->m_image);
	return *resultimage;
}
	
Image& Image::operator*=(const Image& image)
{
    cvMul(m_image, image.m_image, m_image, NULL);
    return *this;
}
	
Image& Image::operator!()
{
	Image* resultimage = new Image(size(), depth(), numberOfChannels());
	cvNot(m_image, resultimage->m_image);
	return *resultimage;
}
	
Image& Image::operator&(const Image& image)
{
	Image* resultimage = new Image(size(), depth(), numberOfChannels());
	cvAnd(m_image, image.m_image, resultimage->m_image, NULL);
	return *resultimage;
}
	
Image& Image::operator&=(const Image& image)
{
	cvAnd(m_image, image.m_image, m_image, NULL);
	return *this;
}
	
Image& Image::operator|(const Image& image)
{
	Image* resultimage = new Image(size(), depth(), numberOfChannels());
	cvOr(m_image, image.m_image, resultimage->m_image, NULL);
	return *resultimage;
}
	
Image& Image::operator|=(const Image& image)
{
	cvOr(m_image, image.m_image, m_image, NULL);
	return *this;
}
	
Image& Image::operator^(const Image& image)
{
	Image* resultimage = new Image(size(), depth(), numberOfChannels());
	cvXor(m_image, image.m_image, resultimage->m_image, NULL);
	return *resultimage;
}
	
Image& Image::operator^=(const Image& image)
{
	cvXor(m_image, image.m_image, m_image, NULL);
	return *this;
}
    
Image& Image::absDiff(const Image& image)
{
    Image * resultimage = new Image(size(), depth(), numberOfChannels());
    cvAbsDiff(m_image, image.m_image, resultimage->m_image);
    return *resultimage;
}
    
	
#ifdef DEBUG
void Image::showImage(const char* windowName)
{
	cvNamedWindow(windowName, 0);
	cvShowImage(windowName, m_image);
	cvWaitKey(10);	//delay to draw window
}
#endif
	
} // namespace Bitmap
    
} // namespace OpenCV
