/*-
 * Copyright (c) 2009 Ander Suarez and Endika Gutiérrez, University of Deusto
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


/**
 *  \file VideoCapture.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 08/04/09
 */


#ifndef VideoCapture_h
#define VideoCapture_h

//#include "include/OpenCV.h"
#include "include/Exception.h"
//#include "Image.h"
#include "Capture.h"

namespace OpenCV {
    namespace VideoIO {
        /**
         *  VideoCapture
         *  Captures video from file. Inherits from Capture.
         */
        class VideoCapture : public Capture {
        public:
// Constructors
            VideoCapture();
            VideoCapture(const VideoCapture&);
            /**
             *  Default Constructor
             *  \param  [in]    filename    Video Source file
             *  \throw  FileNotFoundException if file does not exists or can't be opened.
             */
            VideoCapture(const char*) throw (FileNotFoundException);
            virtual ~VideoCapture();
            
// Getters & Setters
            /// Gets count of total frames
            inline long framesCount() { return (long)cvGetCaptureProperty(m_capture, CV_CAP_PROP_FRAME_COUNT); }
            /// Gets frames per second
            inline double fps() { return (double)cvGetCaptureProperty(m_capture, CV_CAP_PROP_FPS); }
            /// Gets frame's size
            inline CvSize frameSize() { return cvSize((int)cvGetCaptureProperty(m_capture, CV_CAP_PROP_FRAME_WIDTH), 
                                                      (int)cvGetCaptureProperty(m_capture, CV_CAP_PROP_FRAME_HEIGHT)); }
            /// Gets video FOURC code of codec
            inline int fourCharCode() { return (int)cvGetCaptureProperty(m_capture, CV_CAP_PROP_FOURCC); }
        };
	} // namespace VideoIO
} // namespace OpenCV

#endif // VideoCapture_h



