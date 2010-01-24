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
 *  \file HaarClassifier.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 25/01/09
 */

#ifndef HaarClassifier_h
#define HaarClassifier_h

#include <vector>
#include "include/OpenCV.h"
#include "include/Exception.h"
#include "Image.h"

namespace OpenCV {
    namespace MachineLearning {
        using namespace Bitmap;
    
        const int HAAR_IMAGE_WIDTH = 320;
        const int HAAR_IMAGE_HEIGHT = 240;
    
        typedef std::vector<CvRect> FoundObjects;

        /**
         *  HaarClassifier
         *  Implements Viola-Jones algorithms for patterns recognition.
         *  Patern must be in haar cascade XML file.
         */
        class HaarClassifier {
        public:
// Constructors
            HaarClassifier();
            /**
             *  Default Constructor
             *  Gets classifier from xml file
             *  \param  [in]    filename    Haar Cascade's file name
             *  \throw  FileNotFoundException   Throws if file can't be opened.
             */
            explicit HaarClassifier(const char*)
                throw (FileNotFoundException);
            HaarClassifier(const HaarClassifier&);
            virtual ~HaarClassifier();
        
            /**
             *  Gets classifier from xml file
             *  \param  [in]    filename    Haar Cascade's file name
             *  \throw  FileNotFoundException   Throws if file can't be opened.
             */
            void loadClassifier(const char*)
                throw (FileNotFoundException);
        
// Public Methods
            /**
             *  Finds Object for loaded pattern
             *  \param  [in]    image       Image in wich find objects
             *  \param  [in]    scaleFactor Scale Factor
             *  \param  [in]    minNeightbors   Minimum neightbours
             *  \param  [in]    flags       Flags. View OpenCV'sDoucumentation
             *  \param  [in]    minSize     Found object's minimum Size
             *  \return Vector of found objects' rect;
             */
            FoundObjects* findObjects(const Image*, double = 1.1l, int = 3, int = 0, CvSize = cvSize(0, 0)) const;
        
        protected:
            CvHaarClassifierCascade* m_classifier;
            CvMemStorage * m_storage;
        };
    } // namespace MachineLearning
} // namespace OpenCV

#endif // HaarClassifier_h
