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
 *  \file MultipleTracker.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 19/02/09
 */

#ifndef MultipleTracker_h
#define MultipleTracker_h

#include <vector>

#include "Macros.h"
#include "include/OpenCV.h"
//#include "Image.h"
#include "Tracker.h"

#define USE_MULTITHREAD

namespace OpenCV {
    namespace Tracking {
        /**
         *  Multiple trackers
         *  Implements methods for tracking by multiple algorithms.
         */
        class MultipleTracker : public Tracker {
        public:
// Constructors
            MultipleTracker();
            MultipleTracker(const MultipleTracker&);
            /**
             *  Default Constructor
             *  \param  [in]    trackers    Vector of custom trackers.
             *
             */
            MultipleTracker(std::vector<Tracker*>*);
            virtual ~MultipleTracker();
            
// Public Methods
            /**
             *  Start tracking.
             *  \param  [in]    image   Image to start tracking
             *  \param  [in]    connectedComps  Object to be tracked
             */
            virtual void startTracking(const Image*, const CvConnectedComp*);

            /**
             *  Tracks object on image.
             *  \param  [in]    image   Image to be tracked
             *  \return ConnectedComponent of new object.
             */
            virtual CvConnectedComp* track(const Image*);
            
        protected:
            std::vector<Tracker*>* m_trackers;
            
        private:
// Private Methods
            CvRect defaultRect(CvRect*, int); 
            
        };
    } // namespace Tracking
} // namespace OpenCV 


#endif // MultipleTracker_h

