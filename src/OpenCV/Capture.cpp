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


#include "Capture.h"

namespace OpenCV {
    
namespace VideoIO {
	
Capture::Capture()
    : m_capture(NULL)
    , m_capturedImage(NULL)
{
}
    
Capture::Capture(const Capture& capture)
    : m_capture(capture.m_capture)  /* Capture is Readonly, don't copy */
    , m_capturedImage(NULL)
{
}

Capture::~Capture()
{
    cvReleaseCapture(&m_capture);
}
	
Image*& Capture::captureFrame()
{
    /* This is volatile because capturedImage 
     * is alwais storaged in same address */
    /* Use captureFrame() instead of image = captureFrame() */
    if (m_capture)
        if (!m_capturedImage)
            m_capturedImage = new Image(cvQueryFrame(m_capture));
        else
            cvQueryFrame(m_capture);
    return m_capturedImage;
}
    
Capture::Capture(CvCapture* cvCapture)
    : m_capture(cvCapture)
    , m_capturedImage(NULL)
{
}
	
} // namespace VideoIO
    
} // namespace OpenCV
