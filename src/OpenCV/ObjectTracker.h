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
 *  \file ObjectTracker.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 25/02/09
 */

#ifndef ObjectTracker_h
#define ObjectTracker_h

#include "include/Macros.h"

#include "include/OpenCV.h"
//#include "Image.h"
//#include "Histogram.h"
#include "OpticalObject.h"
#include "MeanShift.h"

using namespace OpenCV;
using namespace VectorizedGraphics;

namespace OpenCV {
    namespace Tracking {
        const double MIN_PERIMETER_TO_TRACK = 32.0;
        const double MIN_PROBABILITY = 0.25;
        
        /**
         *  ObjectTracker
         *  OpticalObject based Tracked by color.
         */
        class ObjectTracker : public MeanShift {
        public:
// Constructors
            ObjectTracker();
            ObjectTracker(const ObjectTracker&);

            /**
             *  Constructor and start tracking.
             *  \param  [in]    image   Image to start tracking
             *  \param  [in]    rect    Object's rect to be tracked
             */
            ObjectTracker(Image*, CvRect);
            /**
             *  Constructor and start tracking.
             *  \param  [in]    image   Image to start tracking
             *  \param  [in]    cComp   Object to be tracked
             */
            ObjectTracker(Image*, CvConnectedComp*);
            /**
             *  Constructor and start tracking.
             *  \param  [in]    image   Image to start tracking
             *  \param  [in]    object OpticalObject to be tracked
             */
            ObjectTracker(Image*, OpticalObject*);
            /**
             *  Constructor and start tracking.
             *  \param  [in]    histogram   Histogram of the objetc to be tracked
             *  \param  [in]    object      Object's rect to be tracked
             */
            ObjectTracker(Histogram*, OpticalObject*);
            
            virtual ~ObjectTracker();
            
// Getters and Setters
            inline void setLastPosition(CvRect rect) { m_lastPostition = rect; }
            void setTrackingHistogram(Histogram*);
            void setOpticalObject(OpticalObject*);
            inline CvRect lastPosition() { return m_lastPostition; }
            inline Histogram* trackingHistogram() { return m_trackingHist; }
            inline OpticalObject* trackingObject() { return m_trackingObject; }
            
// Public Methods
            /**
             *  Start tracking.
             *  \param  [in]    image   Image to start tracking
             *  \param  [in]    cComp   Object to be tracked
             */
            virtual void startTracking(Image*, CvConnectedComp*);
            /**
             *  Start tracking.
             *  \param  [in]    image   Image to start tracking
             *  \param  [in]    oObj    Object to be tracked
             */
            virtual void startTracking(Image*, OpticalObject*);
            
            /**
             *  Tracks object on image.
             *  \param  [in]    image   Image to be tracked
             *  \return OpticalObject of new position.
             */
            OpticalObject* trackObject(const Image*, const Mask* = NULL);
            /**
             *  Tracks object on image.
             *  \param  [in]    image   Image to be tracked
             *  \return ConnectedComponent of new object.
             */
            virtual CvConnectedComp* track(const Image* image, const Mask* probabilisticMask = NULL) { return trackObject(image, probabilisticMask)->connectedComponents(); }
            
        protected:
            OpticalObject* m_trackingObject;
            
        private:
// Private Methods
            double probabilityOfNewPosition(CvRect, CvRect); //return value [0, 1] of probability
            
        };
    } // namespace Tracking 
} // namespace OpenCV

#endif // ObjectTracker_h

