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
 *  \file OpticalFlow.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 21/12/08
 */

#ifndef OpticalFlow_h
#define OpticalFlow_h

#include <vector>

#include "include/OpenCV.h"
#include "Image.h"

namespace OpenCV {
    using namespace Bitmap;
    namespace VectorizedGraphics {

        /// 2D vector of float values.
        struct Vector2D32f {
            CvPoint2D32f p0, p1;
            
            inline Vector2D32f() {
                p0.x = 0.0f;
                p0.y = 0.0f;
                p1.x = 0.0f;
                p1.y = 0.0f;
            }
            
            inline Vector2D32f operator+(Vector2D32f& vAdd) {
                Vector2D32f v;
                v.p0.x = p0.x + vAdd.p0.x;
                v.p0.y = p0.y + vAdd.p0.y;
                v.p1.x = p1.x + vAdd.p1.x;
                v.p1.y = p1.y + vAdd.p1.y;
                return v;
            }
            
            inline Vector2D32f& operator+=(Vector2D32f& vAdd) {
                p0.x += vAdd.p0.x;
                p0.y += vAdd.p0.y;
                p1.x += vAdd.p1.x;
                p1.y += vAdd.p1.y;
                return *this;
            }
            
            inline Vector2D32f operator-(Vector2D32f& vSub) {
                Vector2D32f v;
                v.p0.x = p0.x - vSub.p0.x;
                v.p0.y = p0.y - vSub.p0.y;
                v.p1.x = p1.x - vSub.p1.x;
                v.p1.y = p1.y - vSub.p1.y;
                return v;
            }
            
            inline Vector2D32f& operator-=(Vector2D32f& vSub) {
                p0.x -= vSub.p0.x;
                p0.y -= vSub.p0.y;
                p1.x -= vSub.p1.x;
                p1.y -= vSub.p1.y;
                return *this;
            }
            
            inline Vector2D32f operator/(float n) {
                Vector2D32f v;
                v.p0.x = p0.x / n;
                v.p0.y = p0.y / n;
                v.p1.x = p1.x / n;
                v.p1.y = p1.y / n;
                return v;
            }
            
            inline Vector2D32f& operator/=(float n) {
                p0.x /= n;
                p0.y /= n;
                p1.x /= n;
                p1.y /= n;
                return *this;
            }
            
            inline float dx() { return p1.x - p0.x; }
            
            inline float dy() { return p1.y - p0.y; }

            inline float length() { return sqrt(pow(dx(), 2) + pow(dy(), 2)); }
            
        };
        
        typedef std::vector<Vector2D32f> Flow;
        
        /**
         *  OpticalFlow
         *  Abstarct class for diferent Optical flow algorithms
         */
        class OpticalFlow {
        public:
            /**
             *  Learns image for generate optical flow after.
             *  \param  [in]    image   Image to be seeded
             */
            virtual void seedImage(Image*) { }
            
            /**
             *  Calculates optical flow from seeded image
             *  \param  [in]    image   Image in witch calculate optical flow.
             *  \return Flow as 2D vectors array.
             */
            virtual Flow* calcOpticalFlow(Image*) { return NULL; }
        };
        
    } // namespace VectorizedGraphics
} // namespace OpenCV

#endif // OpticalFlow_h
