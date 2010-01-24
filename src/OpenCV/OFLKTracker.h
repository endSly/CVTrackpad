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
 *  \file OFLKTracker.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 27/01/09
 */

#ifndef OFLKTracker_h
#define OFLKTracker_h

#include "math.h"

#include "include/Macros.h"
#include "include/OpenCV.h"
//#include "Image.h"
#include "Tracker.h"
#include "DrawableImage.h"
#include "OpticalFlowLK.h"

namespace OpenCV {
    namespace Tracking {
        using namespace VectorizedGraphics;

        const unsigned int MAX_POINTS_TO_TRACK = 64;
        const double BACKGROUNG_VECTOR_LENGHT = 4.0l;   /* Max length of vector to be skiped */

        /**
         *  OFLKTracker
         *  Implements tracking algorithm based on Lucas-Kanade optical
         *  flow that not depends of object's color.
         */
        class OFLKTracker : public Tracker {
        public:
// Constructors
            OFLKTracker() { }
            OFLKTracker(const OFLKTracker&);
            /**
             *  Constructor and start tracking.
             *  \param  [in]    image   Image to start tracking
             *  \param  [in]    cc      Object to be tracked
             */
            OFLKTracker(const Image*, const CvConnectedComp*);
            /**
             *  Constructor and start tracking.
             *  \param  [in]    image   Image to start tracking
             *  \param  [in]    rect    Object's rect
             *  \param  [in]    mask    Object's mask
             */
            OFLKTracker(const Image*, CvRect, const Mask* = NULL);
            virtual ~OFLKTracker();
            
// Public Methods
            /**
             *  Constructor and start tracking.
             *  \param  [in]    image   Image to start tracking
             *  \param  [in]    cComp   Object to be tracked
             */
            virtual void startTracking(const Image*, const CvConnectedComp*);
            /**
             *  Constructor and start tracking.
             *  \param  [in]    image   Image to start tracking
             *  \param  [in]    rect    Object's rect
             *  \param  [in]    mask    Object's mask
             */
            virtual void startTracking(const Image*, CvRect, const Mask* = NULL);
            
            /**
             *  Tracks object on image.
             *  \param  [in]    image   Image to be tracked
             *  \return ConnectedComponent of new object.
             */
            virtual CvConnectedComp* track(const Image*, const Mask* = NULL);
            
        protected:
            OpticalFlowLK* m_oflk;
            CvRect m_lastPosition;
            
        private:
// Private Methods
            static Vector2D32f standardVector(Flow*);
        };
        
    } // namespace Tracking
    
} // namespace OpenCV

#endif // OFLKTracker_h
