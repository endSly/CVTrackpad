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


#include "ScreenCapture.h"

namespace HumanInterface {

ScreenCapture::ScreenCapture(Capture& capture, CvPoint2D32f* corners)
	: Capture(capture)
	, m_corners(corners)
{
}
	
	
ScreenCapture::ScreenCapture(Capture& capture, ScreenRecognizer& sr)
	: Capture(capture)
	, m_corners(sr.m_corners)
{	
}
	
ScreenCapture::~ScreenCapture()
{
	for (int i = 0; i < 3; i++)
		delete &m_corners[i];
}

Image* ScreenCapture::trimToScreen(Image* image)
{
	if (!m_corners)
		return image;
	
	ProcessableImage* pimage = new ProcessableImage((ProcessableImage)*image);
	Image* warpimage = pimage->warpPerspective(m_corners);
    delete pimage;
    
    return warpimage;
}
	
Image*& ScreenCapture::captureFrame()
{
	Image* image = (Image*)Capture::captureFrame();
        delete m_capturedImage;
        m_capturedImage = trimToScreen(image);
        return m_capturedImage;
}

} // namespace HumanInterface

