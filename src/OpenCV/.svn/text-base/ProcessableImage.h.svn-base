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
 *  \file ProcessableImage.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 19/11/08
 */

#ifndef ProcessableImage_h
#define ProcessableImage_h

#include "include/OpenCV.h"

#include "Image.h"

namespace OpenCV {
    namespace Bitmap {
        /// Threshold result type
        enum ThresholdType {
            Binary = CV_THRESH_BINARY,
            BinaryInv = CV_THRESH_BINARY_INV,
            MaskThres = CV_THRESH_MASK,
            Otsu = CV_THRESH_OTSU,
            ToZero = CV_THRESH_TOZERO,
            ToZeroInv = CV_THRESH_TOZERO_INV,
            Trunc = CV_THRESH_TRUNC
        };
        
        /// Mopholgy operators
        enum MorphologyOperator {
            Blackhat = CV_MOP_BLACKHAT,
            Open = CV_MOP_OPEN,
            Gradient = CV_MOP_GRADIENT,
            Close = CV_MOP_CLOSE,
            Tophat = CV_MOP_TOPHAT
        };
        
        /// Inpaint algorithms. Refer to OpenCV's documantation
        enum InpaintMethod {
            NavierStokes = CV_INPAINT_NS,
            Telea = CV_INPAINT_TELEA
        };
        
        /// Adaptive Thredhold type
        enum AdaptiveThresholdType {
            Mean = CV_ADAPTIVE_THRESH_MEAN_C,
            Gaussian = CV_ADAPTIVE_THRESH_GAUSSIAN_C
        };

        /**
         *  ProcessableImage
         *  Implements methods fore Image processing.
         */
        class ProcessableImage : public Image {
        public:
// Constructors
            ProcessableImage();
            ProcessableImage(const ProcessableImage&);
            ProcessableImage(const Image&);
            /**
             *  Default Constructor
             *  \param  [in]    size        Image's Size
             *  \param  [in]    depth       Image's color depth. By default UByte
             *  \param  [in]    channels    Image's channels count. 3 for color[Default] 1 for B/W
             */
            ProcessableImage(CvSize, int = UByte, int = 3);
            virtual ~ProcessableImage();
            
// Public Methods
            /**
             *  Sets threshold for each pixel of image
             *  \param  [in]    val     New minimum value for each pixel
             *  \param  [in]    max     Maximum value for one pixel. For UByte 255 [Default].
             *  \param  [in]    type    Threshold type. Refers to enum ThresholdType
             */
            void threshold(double, double = 255, int = Binary);
            /**
             *  Sets threshold for each pixel of image
             *  \param  [in]    max     Maximum value for one pixel. For UByte 255 [Default].
             *  \param  [in]    method  New minimum value for each pixel .
             *  \param  [in]    type    Threshold type. Refers to enum ThresholdType.
             *  \param  [in]    blockSize   Path's block size.
             */
            void adaptiveThreshold(double = 255, int = Mean, int = Binary, int = 3);
            
            /**
             *  Warps image's perspective
             *  \param  [in]    currentCorners  Array of 4 points of 4 corners to be warped
             *  \param  [in]    newCorners      Array of 4 points of currentCorners's new position.
             *                                  If NULL newCorners coincides with image's corners
             */
            Image* warpPerspective(CvPoint2D32f*, CvPoint2D32f* = NULL);
            /**
             *  Warps image's perspective
             *  \param  [in]    warpMat     OpenCV's transformation matrix.
             */
            Image* warpPerspective(CvMat*);
            
            /// Finds corners of chessboard on the image.
            CvPoint2D32f* findChessboardCorners(int, int, int = CV_CALIB_CB_ADAPTIVE_THRESH);
            
            /// Applies sobel filter
            inline void sobel(int xOrder, int yOrder, int apertureSize) { cvSobel(m_image, m_image, xOrder, yOrder, apertureSize); }
            /// Applies canny filter
            inline void canny(double threshold1, double threshold2, double apertureSize, Image* dest = NULL) { cvCanny(m_image, dest ? dest->cvImage() : m_image, threshold1, threshold2, apertureSize); }
            
            /**
             *  Applies morphology opeartor
             *  \param  [in]    operation       Morphology Operator, from enum MorphologyOperator
             *  \param  [in]    iterations      Iterations count
             */
            void morphologyEx(int, int = 1);
            /// Mophology operator for color contraction.
            inline void morphologyOpen() { morphologyEx(Open); }
            /// Mophology operator for dilate color.
            inline void morphologyClose() { morphologyEx(Close); }
            
            /// Applies pyramid mean shift filter
            inline void meanShiftFiltering(int maxLevel, int spatialRadius, int colorRadius, Image* dest = NULL) { cvPyrMeanShiftFiltering(m_image, dest ? dest->cvImage() : m_image, spatialRadius, colorRadius, maxLevel); }
            /**
             *  Inpaints "corrupted" image
             *  \param  [in]    mask    Mask with zones to be inpainted
             *  \param  [in]    radius Inpaint's radious
             *  \param  [in]    method  Inpaint's Method, refers to enum InpaintMethod
             */
            inline void inpaint(Mask* mask, double radius, int method = NavierStokes) { cvInpaint(m_image, mask, m_image, radius, method); }
            
        protected:
// Protected Constructors
            ProcessableImage(IplImage*);
            
// Protected Methods
            IplImage* convert(int = CV_RGB2GRAY);
            
        };
    } // namespace Bitmap
} // namespace OpenCV

#endif // ProcessableImage_h
