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
 *  \file BackgroundSubtraction.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 15/04/09
 */

#ifndef BackgroundSubtraction_h
#define BackgroundSubtraction_h

#include <vector>
#include "time.h"
#include "string.h"
#include "include/Macros.h"
#include "Image.h"

#define CHANNELS_COUNT 3

namespace OpenCV {
    namespace Bitmap {
        /**
         *  BackgroundSubtraction
         *  Abstract class for Background substraction
         *  algorithms.
         */
        class BackgroundSubtraction {
        public:
            virtual ~BackgroundSubtraction() { }
            
            virtual void learnBackground(Image*) { }
            virtual Mask* subtractBackground(Image*) { return NULL; }
        };
        
        const CvScalar DEFAULT_BOUND = cvScalar(14, 10, 10);    /* for YUV */
        const CvSize CODEBOOK_RESOLUTION = cvSize(100, 75);
        const unsigned long TIME_TO_ASUME_OBSOLETE = 5 * CLOCKS_PER_SEC;
        const int CLEAR_RATE = 4;
        
        /**
         *  CodeBookEntry
         *  CodeBook's entry.
         */
        struct CodeBookEntry {
            unsigned char learnHigh[CHANNELS_COUNT];
            unsigned char learnLow[CHANNELS_COUNT];
            unsigned char max[CHANNELS_COUNT];
            unsigned char min[CHANNELS_COUNT];
            long lastUpdate;
            long timeOnScene;
        };
        typedef std::vector<CodeBookEntry*> CodeBook;
        
        /**
         *  CodeBookSubstraction
         *  Inherits from BackgroundSubtraction. Implements CodeBook algorithm
         *  for background substraction. Generates one dictionary of last values
         *  of each pixel.
         *  This algorithm learns also not static background.
         */

        class CodeBookSubstraction : public BackgroundSubtraction {
        public:
// Constructors
            CodeBookSubstraction();
            CodeBookSubstraction(const CodeBookSubstraction&);
            /**
             *  Default Constructor
             *  \param  [in]    image    Image of background
             *  \param  [in]    channelsCount   Channels count. 1 faster, 3 better[default]
             */
            CodeBookSubstraction(const Image*, int = CHANNELS_COUNT);
            virtual ~CodeBookSubstraction();
            
// Getters & Setters
            inline CvScalar bounds() const { return m_bounds; }
            inline void setBounds(const CvScalar& bounds) { m_bounds = bounds; }
            
// Public Methods
            /**
             *  Method for learning Background. Must be called as many times as could
             *  be for better performance.
             *  \param  [in]    image   Image of background
             */
            virtual void learnBackground(const Image*);
            /**
             *  Method for Substracting Background. Also learns Background.
             *  Call after learnBackground
             *  \param  [in]    image   Image to be substract
             *  \return Background substraction Mask.
             */
            virtual Mask* subtractBackground(const Image*);
#ifdef DEBUG
            Mask* codeBookDepth();
            Image* generateBackground();
#endif // DEBUG
            
        protected:
// Protected Methods
            unsigned char diffPixel(unsigned char*, CodeBook&);
            CodeBookEntry* updateCodebook(unsigned char*, CodeBook&);
            long clearObsoleteEntries(CodeBook&);
            
            std::vector<CodeBook> m_codeBooksVector;
            CvScalar m_bounds; /* Bounds, 10 by default */
            int m_channelsCount;
            
        private: 
// Private Methods
            inline Image* toYUV(const Image* image) { return Image::convert(image, CV_BGR2YCrCb); }
            
            unsigned long m_lastClearTime;
        };
    } // namespace Bitmap
} // namespace OpenCV

#endif // BackgroundSubtraction_h

