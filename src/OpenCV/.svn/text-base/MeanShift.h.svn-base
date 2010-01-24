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
 *  \file MeanShift.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 22/01/09
 */

#ifndef MeanShift_h
#define MeanShift_h

#include "include/OpenCV.h"
//#include "Image.h"
#include "Histogram.h"
#include "Tracker.h" 

namespace OpenCV {
    namespace Tracking {
        class MeanShift : public Tracker {
        public:
// Constructors
            MeanShift();
            MeanShift(const MeanShift&);
            /**
             *  Constructor and start tracking.
             *  \param  [in]    image   Image to start tracking
             *  \param  [in]    cComp   Object to be tracked
             */
            MeanShift(const Image*, const CvConnectedComp*);
            /**
             *  Constructor and start tracking.
             *  \param  [in]    image   Image to start tracking
             *  \param  [in]    rect    Object's rect to be tracked
             */
            MeanShift(const Image*, CvRect);
            /**
             *  Constructor and start tracking.
             *  \param  [in]    hist    Histogram of the objetc to be tracked
             *  \param  [in]    lastPos Object's rect to be tracked
             */
            MeanShift(const Histogram*, CvRect);
            virtual ~MeanShift();
        
// Public Methods
            /**
             *  Start tracking.
             *  \param  [in]    image   Image to start tracking
             *  \param  [in]    cComp   Object to be tracked
             */
            virtual void startTracking(const Image*, const CvConnectedComp*);
            /**
             *  Start tracking.
             *  \param  [in]    image   Image to start tracking
             *  \param  [in]    rect    Object's rect to be tracked
             */
            virtual void startTracking(const Image*, CvRect);
            /**
             *  Start tracking.
             *  \param  [in]    hist    Histogram of the objetc to be tracked
             *  \param  [in]    lastPos Object's rect to be tracked
             */
            virtual void startTracking(const Histogram*, CvRect);
        
            inline void setLastPosition(CvRect rect) { m_lastPostition = rect; }
            void setTrackingHistogram(const Histogram*);
            inline CvRect lastPosition() const { return m_lastPostition; }
            inline Histogram* trackingHistogram() { return m_trackingHist; }
        
            /**
             *  Tracks object on image.
             *  \param  [in]    image   Image to be tracked
             *  \param  [in]    probabilisticMap    Probabilistic map of tracking position
             *  \return ConnectedComponent of new object.
             */
            virtual CvConnectedComp* track(const Image*, const Mask* = NULL);
        
        protected:
            Histogram* m_trackingHist;
            CvRect m_lastPostition;
            CvConnectedComp m_components;
            
        };
    } // namespace Tracking
} // namespace OpenCV

#endif // MeanShift
