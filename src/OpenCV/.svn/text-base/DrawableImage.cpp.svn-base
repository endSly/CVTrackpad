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


#include "DrawableImage.h"

namespace OpenCV {
    
namespace Bitmap {
	
DrawableImage::DrawableImage(const Image& image)
	: Image(image)
{
}
	
DrawableImage::DrawableImage(IplImage* image)
	: Image(image)
{		
}
	
DrawableImage::DrawableImage(CvSize size, int depth, int channels)
	: Image(size, depth, channels)
{
}
	
DrawableImage::~DrawableImage()
{
    if (m_image)
        cvReleaseImage(&m_image);
}
	
void DrawableImage::drawLine(CvPoint pt1, CvPoint pt2, int thickness, CvScalar color)
{
	cvLine(m_image, pt1, pt2, color, thickness, 0, 0);
}
	
void DrawableImage::drawRectangle(CvPoint pt1, CvPoint pt2, int thinkness, CvScalar color)
{
	cvRectangle(m_image, pt1, pt2, color, thinkness, 0, 0);
}
	
void DrawableImage::drawBox(CvPoint pt1, CvPoint pt2, CvScalar color)
{
	cvRectangle(m_image, pt1, pt2, color, CV_FILLED, 0, 0);
}
	
void DrawableImage::drawCircle(CvPoint center, int radious, CvScalar color, int thickness)
{
	cvCircle(m_image, center, radious, color, thickness, 0, 0);
}
    
void DrawableImage::drawEllipse(CvPoint, float, int, CvScalar, int)
{
    throw "Not implemented exception";
}

void DrawableImage::drawText(const char* text, CvPoint pt, float size, CvScalar color)
{
	CvFont font;
	cvInitFont(&font, 
               CV_FONT_HERSHEY_SIMPLEX, 
               size * 1.0l, 
               size * 1.0l, 
               0.0l, 
               1, 0);
	cvPutText(m_image, text, pt, &font, color);
}
    
void DrawableImage::drawObject(const OpticalObject* object, CvScalar color)
{
    cvDrawContours(m_image, 
                   object->connectedComponents()->contour, 
                   color, 
                   color,
                   -1,
                   CV_FILLED,
                   8);
}
    
void DrawableImage::drawContour(const OpticalObject* object, CvScalar color , int thickness)
{
    cvDrawContours(m_image,
                   object->connectedComponents()->contour,
                   color,
                   cvScalar(0), 
                   -1, 
                   thickness);
}

} // namespace Bitmap
    
} // namespace OpenCV
