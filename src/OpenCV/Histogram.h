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
 *  \file Histogram.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 21/12/08
 */

#ifndef Histogram_h
#define Histogram_h

#include "include/OpenCV.h"
//#include "Image.h"
#include "DrawableImage.h"

namespace OpenCV {
    namespace Bitmap {
        typedef CvArr Signature;
        
        /// Method for Comparison between histograms.
        enum ComparisonMethod {
            Correlation =	CV_COMP_CORREL ,
            ChiSquare =		CV_COMP_CHISQR ,
            Intersection =	CV_COMP_INTERSECT ,
            BhattacharyyaDistance = CV_COMP_BHATTACHARYYA
        };
        
        /// Histogram type: Array or Sparse histogram
        enum HistogramType {
            Array =	 CV_HIST_ARRAY ,
            Sparse = CV_HIST_SPARSE
        };
        
        /// Distance type for EMD2 (Earth Mover's Distance)
        enum DistanceType {
            ManhattanDistance = CV_DIST_L1,
            EuclideanDistance = CV_DIST_L2
        };

        /**
         *  Histogram
         *  Support for probabilistics histograms and methods for it's
         *  manipulation. Provides also utilities for image's histogram
         *  manipulation such as equalize or back project.
         */
        class Histogram {
        public:
// Constructors
            Histogram();
            Histogram(const Histogram&);
            /**
             *  Constructor for a generic Histogram
             *  \param  [in]    dims    Dimensions of the histogram.
             *  \param  [in]    sizes   Size of each dimension.
             *  \param  [in]    ranges  Range for each dimension. Array size: float[2][sizes]
             *  \param  [in]    type    Type of the histogram. HistogramType = { Array , Sparse }
             *  \param  [in]    histToAcomul    Histogram in witch acomulate new histogram.
             */
            Histogram(int, int*, float**, int = Array, Histogram* = NULL);
            virtual ~Histogram();
            
            /* Diferent histogram types constructors */
            /**
             *  Constructor for Image based Hue-Saturation Histogram
             *  \param  [in]    image   BGR Image to generate histogram
             *  \param  [in]    mask    Mask to apply to the image before generrate histogram
             *  \param  [in]    sizeH   Hue dimension Size
             *  \param  [in]    sizeS   Saturation dimension Size
             */
            static Histogram* createHSHistogram(const Image*, const Mask* = NULL, int = 30, int = 32);
            /**
             *  Constructor for Image based RGB Histogram
             *  \param  [in]    image   BGR Image to generate histogram
             *  \param  [in]    mask    Mask to apply to the image before generrate histogram
             */
            static Histogram* createRGBHistogram(const Image*, const Mask* = NULL);
            /**
             *  Constructor for Image based Gray-channel Histogram
             *  \param  [in]    image   BGR Image to generate histogram
             *  \param  [in]    mask    Mask to apply to the image before generrate histogram
             */
            static Histogram* create1ChHistogram(const Image*, const Mask* = NULL);
            
            /// An utility to equalize image's histogram
            static Image* equalizeHist(const Image*);
            
#ifdef DEBUG
            Mask* representInMask(); /* Debug purpouses only */
#endif // DEBUG
            /// Method to copy an histogram
            Histogram* copy() const;
            /// Sets all histogram's value to zero
            inline void clear() { cvClearHist(m_histogram); }
            
// Getters and Setters
            inline double compare(const Histogram* hist, int method = Correlation) const { return cvCompareHist(m_histogram, hist->m_histogram, method); }
            float min() const;
            float max() const;
            float getValue(int, int = 0, int = 0) const;
            inline int dimensions() const { return m_histogram ? m_histogram->mat.dims : 0; }
            inline int dimensionSize(int dimension) const { return m_histogram && (dimension < dimensions()) ? m_histogram->mat.dim[dimension].size : 0; }
            
// Public Methods
            /**
             *  Calcules Earth Mover's Distance
             *  \param  [in]    histogram1   First histogram to compare.
             *  \param  [in]    histogram2   Second histogram to compare.
             *  \param  [in]    distanceType Compare Distance type; From enum DistanceType.
             */
            static float calcEMD2(const Histogram*, const Histogram*, int = EuclideanDistance);
            
            /**
             *  Calcules Earth Mover's Distance
             *  \param  [in]    histogram   Histogram to compare with this.
             *  \param  [in]    distanceType Compare Distance type; From enum DistanceType.
             */
            inline float calcEMD2(const Histogram* histogram, int distanceType = EuclideanDistance) const { return calcEMD2(this, histogram, distanceType); }
            
            /**
             *  Calculates Back Projection
             *  \param  [in]    rgbImage   Image to back project(Must be in RGB)
             *  \return Back projection
             */
            Mask* calcBackProjection(const Image*) const;
            /// Calculates Path Back projection \todo
            Mask* calcPatchBackProjection(const Image*, CvSize, float, int) const;
            
            /// Utility to normalize histogram
            void normalize(double = 1.0l);
            /// Utility to set histograms threshold
            inline void threshold(double threshold) { cvThreshHist(m_histogram, threshold); }
            
        protected:
// Protected Methods
            inline Signature* signature() const { return createSignature(this); }
            static Signature* createSignature(const Histogram*);
            
            CvHistogram* m_histogram;
        };
    } // namespace Bitmap
} // namespace OpenCV


#endif // Histogram_h
