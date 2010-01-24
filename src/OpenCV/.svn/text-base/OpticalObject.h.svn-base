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
 *  \file OpticalObject.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 04/01/09
 */

#ifndef OpticalObject_h
#define OpticalObject_h

#include <vector>

#include "include/OpenCV.h"
//#include "Image.h"
#include "ProcessableImage.h"

namespace OpenCV {
    using namespace Bitmap;
    namespace VectorizedGraphics {
        
        const double DEFAULT_MASK_THRESHOLD = 128.0l;
        const int DEFAULT_POLYGONAL_APPROX_ALG = CV_POLY_APPROX_DP;
        const CvRect CV_RECT_ZERO = cvRect(0, 0, 0, 0);
        
        /// Indicates Object's orientation
        enum Orientation {
            Clockwise = CV_CLOCKWISE, 
            CounterClockwise = CV_COUNTER_CLOCKWISE
        };
        
        /// Algorithms for delimitation of contours
        enum CountoursFindMethod {
            ChainCode = CV_CHAIN_CODE,
            ChainApproxNone = CV_CHAIN_APPROX_NONE,
            ChainApproxSimple = CV_CHAIN_APPROX_SIMPLE,
            ChainApproxTC89L1 = CV_CHAIN_APPROX_TC89_L1, 
            ChainApproxTC89KCOS = CV_CHAIN_APPROX_TC89_KCOS,
            LinksRuns = CV_LINK_RUNS
        };
        
        class OpticalObject;
        
        typedef std::vector<OpticalObject*> OpticalObjects;
        
        /**
         *  OpticalObject
         *  Methods for optical objects given as connected components.
         */
        class OpticalObject {
        public:
// Constructors
            OpticalObject();
            OpticalObject(const OpticalObject&);
            explicit OpticalObject(CvConnectedComp*);

            /**
             *  Default Constructor
             *  Find's all optical objects on image and returns it in a vector.
             *  \param  [in]    image   Image to be processed.
             *  \param  [in]    minPerimeter    Minimum Object's perimeter.
             *  \param  [in]    method  Algorithm to find objects.
             */
            static OpticalObjects* opticalObjectsFromImage(const Image*,
                                                           double = 32.0l, 
                                                           int = ChainApproxSimple); 
            virtual ~OpticalObject();
            
            /**
             *  Generates boolean mask with connected components.
             *  \param  [in]    mask    Mask to be processed.
             *  \param  [in]    minPerimeter    Minimum Object's perimeter.
             *  \return Boolean Mask
             */
            static Mask* maskFromUnconnectedMask(const Mask*, double = 32.0l);
            
// Getters and Setters
            /// Gets object area in pixels
            double area() const;
            /// Gets bounding rect
            CvRect rect() const;

            inline CvConnectedComp* connectedComponents() const { return m_objectComponents; }
            
            /// Draws object in Mask
            Mask* toMask() const;
            
// Public Methods
            /// \todo
            OpticalObject* convexHull(int = Clockwise, int = 0);
            /// \todo
            inline int checkConvexity() { return cvCheckContourConvexity(m_objectComponents->contour); }
            /// \todo
            static OpticalObjects* convexityDefects(OpticalObject*, OpticalObject*);
            
            /// Returns true if object is over rect
            bool isOnRect(const CvRect&);
            /// Calculates minimum distance to point
            inline double distanceTo(const CvPoint& pt) { return sqrt(pow(pt.x - (rect().x + rect().width / 2), 2) + pow(pt.y - (rect().y + rect().height / 2), 2)); }
            /// Calculates minimum distance to center of rect
            inline double distanceTo(const CvRect& r) { return distanceTo(cvPoint(r.x + r.width / 2, r.y + r.height / 2)); }
            
        protected:
            CvConnectedComp* m_objectComponents;
            
        private:
// Private Methods
            static CvSeq* polygonalContours(Image*, int, double);
            
        };
    } // namespace VectorizedGraphics
} // namespace OpenCV


#endif // OpticalObject_h
