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
 *  \file DrawableImage.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 14/11/08
 */

#ifndef DrawableImage_h
#define DrawableImage_h

#include "include/OpenCV.h"

#include "Image.h"
#include "OpticalObject.h"

namespace OpenCV {
    namespace Bitmap {
        using namespace VectorizedGraphics;
        
        const CvScalar COLOR_WHITE =    cvScalar(255, 255, 255);   
        const CvScalar COLOR_GRAY =     cvScalar(127, 127, 127);   
        const CvScalar COLOR_BLACK =    cvScalar(0, 0, 0);
        const CvScalar COLOR_BLUE =     cvScalar(255, 0, 0);        //For BGR only
        const CvScalar COLOR_GREEN =    cvScalar(0, 255, 0);
        const CvScalar COLOR_RED =      cvScalar(0, 0, 255);
        
        /**
         *  DrawableImage
         *  Implements Image's Methods for it's modification by
         *  drawing.
         */
        class DrawableImage : public Image {
        public:
// Constructors
            DrawableImage(const Image&);
            explicit DrawableImage(IplImage*);
            /**
             *  Default Constructor
             *  \param  [in]    size        Image's Size
             *  \param  [in]    depth       Image's color depth. By default UByte
             *  \param  [in]    channels    Image's channels count. 3 for color[Default] 1 for B/W
             */
            DrawableImage(CvSize, int = UByte, int = 3);
            virtual ~DrawableImage();
            
// Public Methods
            void drawLine(CvPoint, CvPoint, int, CvScalar);
            void drawRectangle(CvPoint, CvPoint, int, CvScalar);
            void drawBox(CvPoint, CvPoint, CvScalar);
            void drawCircle(CvPoint, int, CvScalar, int);
            void drawEllipse(CvPoint, float, int, CvScalar, int);
            void drawText(const char*, CvPoint, float, CvScalar);
            void drawObject(const OpticalObject*, CvScalar);
            void drawContour(const OpticalObject*, CvScalar, int);

            /// Clears Image setting all his pixels to 0 (Black)
            inline void clear() { drawBox(cvPoint(0, 0), cvPoint(size().width, size().height), cvScalar(0)); }
            
            inline void drawRectangle(CvRect rect, int width, CvScalar color) { drawRectangle(cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height), width, color); }
            inline void drawBox(CvRect rect, CvScalar color) { drawBox(cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height), color); }
        };
    } // namespace Bitmap
} // namesapce OpenCV

#endif //DrawableImage_h
