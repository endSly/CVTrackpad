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
 *  \file Hand.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 04/03/09
 */

#ifndef Hand_h
#define Hand_h

#include "Macros.h"

#include <vector>
#include <map>

//#include "OpenCV/Image.h"
#include "OpenCV/Histogram.h"
#include "OpenCV/HaarClassifier.h"
#include "OpenCV/OpticalObject.h"

//#include "OpenCV/Tracker.h"
//#include "OpenCV/MeanShift.h"
#include "OpenCV/CAMShift.h"
#include "OpenCV/OFLKTracker.h"


namespace HumanInterface {
    using namespace std;
    using namespace OpenCV;
    using namespace Tracking;
    using namespace VectorizedGraphics;
    using namespace MachineLearning;

    /// Minimum value to asume correct correlation [0, 1]
    const double CORRELATION_THRESHOLD = 0.4l;
    /// Minimum perimeter to find objects
    const double MINIMUM_PERIMETER = 20.0l;
    /// Maximum number of hands to be returned
    const int MAX_HANDS_TO_TRACK = 2;

    /// Entry  for one tracked hand
    struct HandPositionEntry {
        CvRect lastPosition;
        CvPoint2D32f lastVector;    // Not really a point
        float lastArea;
        unsigned long long timeTracked, lastTimeTracked;
    };
    class Hand;

    /**
     *  HandServer
     *  Provides Methods for find hand in one Image from
     *  several input forms.
     */
    class HandServer {
    public:
// Constructors
        HandServer(const HandServer&);
        /// Hand will be found by face classifier
        HandServer(HaarClassifier*);
        /// Hand will be found by hand Histogram
        HandServer(Histogram*);

        virtual ~HandServer();

// Public Methods
        /** Find all hands present in image
          * \param  [in]    image   Image in to search hands
          * \return Vector of all hands found
          */
        vector<Hand*>* findAllHands(const Image*, const Mask* = NULL);
        /// Gets face's rect
        inline CvRect faceRect() const { return m_faceRect; }

    protected:
        HaarClassifier* m_faceClassifier;
        Histogram* m_handHistogram;

    private:
        /// Finds face and updates m_faceSkinHistogram and m_faceRect
        void findFace(const Image*);
        /// Obtains Prabilistic map (Mask)
        Mask* handsProbabilisticMap(const Image*);
        /// Updates historial
        void updateHistorial(const vector<Hand*>&);
        /// Evaluates if is valid and arrange vector by best mach
        int evaluateFoundObjects(vector<OpticalObject*>&, const Image*);

        /* Used only for face classifier */
        Histogram* m_faceSkinHistogram;
        CvRect m_faceRect;

        vector<HandPositionEntry> m_handsHistorial;
    };


    /**
     *  Hand
     *  Interface for Hand's Optical Object
     */
    class Hand : public OpenCV::OpticalObject {
    public:
// Constructors
        Hand(const OpticalObject*, const Image*);
        Hand(const OpticalObject*, Histogram* = NULL);
        virtual ~Hand();
    
// Getters & Setters
        /// Getter for skin Color
        inline Histogram* skinColor() const { return m_skinColor; }
    
// Public Methods
        /// Generates tracker for hand.
        template <class t_tracker>
        t_tracker* handTracker(const Image* image = NULL) { return new t_tracker(image, this->connectedComponents()); }

    protected:
        Histogram* m_skinColor;

};

} // namespace HumanInterface

#endif // Hand_h


