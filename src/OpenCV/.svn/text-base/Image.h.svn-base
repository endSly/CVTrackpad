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
 *  \file Image.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 14/11/08
 */

#ifndef Image_h
#define Image_h

#include "include/OpenCV.h"
#include "include/Exception.h"

namespace OpenCV {
    namespace Bitmap {
        class Image;
        /// Mask is a one channel Image
        typedef Image Mask;
        
        /// Diferent Methods to interpolate an image
        enum InterpolationMethod {
            Nearest = CV_INTER_NN,
            Bilineal = CV_INTER_LINEAR,
            AreaResampling = CV_INTER_AREA,
            Bicubic = CV_INTER_CUBIC
        };
        
        /// Image's channel's depth
        enum Depth {
            UByte = IPL_DEPTH_8U,
            SByte = IPL_DEPTH_8S,
            UShort = IPL_DEPTH_16U,
            SShort = IPL_DEPTH_16S,
            SLong = IPL_DEPTH_32S,
            Float32 = IPL_DEPTH_32F,
            Float64 = IPL_DEPTH_64F
        };
        
        /// Color type Conversion
        enum Conversion {   /* Typical conversions */
            ColorToGray = CV_BGR2GRAY,
            GrayToColor = CV_GRAY2BGR,
            ColorToHSV = CV_BGR2HSV,
            HSVToColor = CV_HSV2BGR,
            ColorToYUV = CV_BGR2YCrCb,
            YUVToColor = CV_BGR2YCrCb
        };

        /**
         *  Image
         *  Implements General Constructors an utilities for
         *  manipulate images or CvArray-based Matrix
         */
        class Image {
        public:
// Constructors
            Image();
            Image(const Image&);
            Image(IplImage*);
            explicit Image(const char*) throw (FileNotFoundException);
            /**
             *  Default Constructor
             *  \param  [in]    size        Image's Size
             *  \param  [in]    depth       Image's color depth. By default UByte
             *  \param  [in]    channels    Image's channels count. 3 for color[Default] 1 for B/W
             */
            Image(CvSize, int = UByte, int = 3);
            virtual ~Image();
            /**
             *  Utility to convert Image's Color type
             *  \param  [in]    image       Image to be converted
             *  \param  [in]    flags       Conversion Flags, from enum Conversion
             *  \return Converted Image
             */
            static Image* convert(const Image*, int);
            /**
             *  Utility to convert Image's Color type
             *  \param  [in]    image       Image to be converted
             *  \param  [in]    newSize     Returned image's new size
             *  \param  [in]    method      Resize Method. From enum InterpolationMethod
             *  \return Resized Image
             */
            static Image* resize(const Image*, CvSize, int = Nearest);
            
// Getters & Setters
            /// Gets Image's Size
            inline CvSize size() const { return cvSize(m_image->width, m_image->height); }
            inline int width() const { return m_image->width; }
            inline int height() const { return m_image->height; }
            /// Gets Color Depth from enum Depth
            inline int depth() const { return m_image->depth; }
            /// Gets channels Count. 3 for color or 1 for BW
            inline int numberOfChannels() const { return m_image->nChannels; }
            /// Gets pointer for image's RAW data(Bitmap). Be careful with big-endian processors
            inline char* rawData() { return m_image->imageData; } 
            
            /// Gets pointer to OpenCV's image format
            inline IplImage* cvImage() const { return m_image; }
            /// Sets OpenCV's Image. It does not delete last image.
            inline void setCvImage(IplImage* cvImage) { m_image = cvImage; }
            
// Public Operators
            /// Only compare pointers
            int    operator==(const Image&);
            /// Operator for copy image.
            Image& operator=(const Image&);
            /// Logical Add for each pixel
            Image& operator+(const Image&);
            /// Logical Acomulate for each pixel
            Image& operator+=(const Image&);
            /// Logical Substraction for each pixel
            Image& operator-(const Image&);
            /// Logical Substraction for each pixel
            Image& operator-=(const Image&);
            /// Matrix multiply
            Image& operator*(const Image&);
            /// Matrix Multiply
            Image& operator*=(const Image&);
            /// Multiply each pixel     \todo
            Image& operator*(double);
            /// Multiply each pixel     \todo
            Image& operator*=(double);
            /// Divide each pixel
            inline Image& operator/(double value) { return (*this) * (1.0l / value); }
            /// Divide each pixel
            inline Image& operator/=(double value) { return (*this) *= (1.0l / value); }
            /// Logical binary Not for each pixel
            Image& operator!();
            /// Logical binary And for each pixel
            Image& operator&(const Image&);
            /// Logical binary And for each pixel
            Image& operator&=(const Image&);
            /// Logical binary Or for each pixel
            Image& operator|(const Image&);
            /// Logical binary Or for each pixel
            Image& operator|=(const Image&);
            /// Logical binary Xor for each pixel
            Image& operator^(const Image&);
            /// Logical binary Xor for each pixel
            Image& operator^=(const Image&);
            /// Absolute difference for each pixel
            Image& absDiff(const Image&);
            
// Public Methods
            /// Copy's the image in separete region of memory
            Image* clone() const;
            /**
             *  Utility to convert Image's Color type
             *  \param  [in]    newSize     Returned image's new size
             *  \param  [in]    method      Resize Method. From enum InterpolationMethod
             */
            void resize(CvSize, int = Nearest);
            /**
             *  Utility to convert this Image's Color type
             *  \param  [in]    flags       Conversion Flags, from enum Conversion
             */
            void convert(int);
            /// Flips Image horizontaly
            inline void flip() { cvFlip(m_image, m_image, 1); }
#ifdef DEBUG
            void showImage(const char*);
#endif // DEBUG
            
        protected:
            IplImage* m_image;
        };
    } // namespace Bitmap
} // namesapce OpenCV

#endif //Image_h
