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
 *  \file OpticalFlowLK.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 24/01/09
 */

#ifndef OpticalFlowLK_h
#define OpticalFlowLK_h

#include <vector>

#include "include/OpenCV.h"
//#include "Image.h"
#include "OpticalFlow.h"

namespace OpenCV {
    namespace VectorizedGraphics {
        /// Default limit for features count.
        const int DEFAULT_TRACK_COUNT = 256;
        
        /**
         *  OpticalFlowLK
         *  Implements Lucas-Kanade algorithm for optical flow
         *  calculation.
         */
        class OpticalFlowLK : public OpticalFlow {
        public:
            OpticalFlowLK();
            OpticalFlowLK(const OpticalFlowLK&);
            /**
             *  Default Constructor
             *  \param  [in]    image       Image to be seeded
             *  \param  [in]    mask        Mask to skip vectors
             *  \param  [in]    featCount   Maximum features count
             *  \param  [in]    qualityLevel    Quality level. More qualiy involves more time
             *  \param  [in]    minDistance Minimum vector length
             *  \param  [in]    blockSize   View OpenCV's documantation
             *  \param  [in]    useHarris   View OpenCV's documantation
             *  \param  [in]    k           View OpenCV's documantation
             */
            OpticalFlowLK(const Image*,
                          const Mask* = NULL,
                          int = DEFAULT_TRACK_COUNT, 
                          double = .01l, 
                          double = 5.0l, 
                          int = 3, 
                          int = 0, 
                          double = .4l);
            virtual ~OpticalFlowLK();
            
            /// Sets features count limit
            inline void setFeaturesCount(int count) { m_maxTrackCount = count; }
            /// Gets features count limit
            inline int featuresCount() const { return m_maxTrackCount; }
            
            /**
             *  Learns image for generate optical flow after.
             *  \param  [in]    image   Image to be seeded
             *  \param  [in]    mask    Mask to skip vectors
             */
            void seedImage(const Image*, const Mask* = NULL);

            /**
             *  Calculates optical flow from seeded image
             *  \param  [in]    image   Image in witch calculate optical flow.
             *  \return Flow as 2D vectors array.
             */
            Flow* calcOpticalFlow(const Image*);
            
        protected:
            Image* m_lastimage;
            int m_maxTrackCount;
            int* m_trackCount;
            IplImage* m_pyramidA;
            IplImage* m_pyramidB;
            IplImage* m_eigen;
            IplImage* m_temp;
            CvPoint2D32f* m_featuresA;
            CvPoint2D32f* m_featuresB;
            float* m_featuresErrors;
            double m_qualityLevel;
            double m_minDistance;
            int m_blockSize; 
            int m_useHarris;
            double m_k;
        };
        
    } // namespace VectorizedGraphics
} // namespace OpenCV

#endif // OpticalFlowLK_h

