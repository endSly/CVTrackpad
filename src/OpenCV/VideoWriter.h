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


/**
 *  \file VideoWriter.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 23/01/09
 */

#ifndef VideoWriter_h
#define VideoWriter_h

#include "include/OpenCV.h"
#include "Image.h"

namespace OpenCV {
    using namespace Bitmap;
    namespace VideoIO {
        /// Four characters Code for Motion JPEG
        const int FOURCC_MJPG = CV_FOURCC('M','J','P','G');
        
        /**
         *  VideoWriter
         *  Methods for Video files creation and modification.
         */
        class VideoWriter {
        public:
// Constructors
            VideoWriter();
            VideoWriter(const VideoWriter&);
            /**
             *  Default Constructor
             *  \param  [in]    filename    Video Source file.
             *  \param  [in]    fps         Frames per Second.
             *  \param  [in]    size        Video's frame size.
             *  \param  [in]    isColor     0 for BW video or !0 for Color video.
             *  \param  [in]    fourcc      Codec's code. FOURCC_MJPG for MotionJPEG.
             *  \throw  FileNotFoundException if file does not exists or can't be opened.
             */
            VideoWriter(const char*, double, CvSize, int = true, int = FOURCC_MJPG);
            virtual ~VideoWriter();
            
// Public Methods
            /**
             *  Writes frame at the end of video
             *  \param  [in]    image   Frame to be written.
             */
            virtual void writeFrame(const Image*);
            
        protected:
            CvVideoWriter* m_writer;
        };
    } // namespace VideoIO
} // namespace OpenCV

#endif // VideoWriter
