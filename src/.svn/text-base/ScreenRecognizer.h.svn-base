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
 *  \file ScreenRecognizer.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 19/11/08
 */

#ifndef ScreenRecognizer_h
#define ScreenRecognizer_h

#include "OpenCV.h"
#include "OpenCV/Capture.h"
#include "OpenCV/Image.h"
#include "OpenCV/ProcessableImage.h"
#include "OpenCV/DrawableImage.h"

using namespace OpenCV;
using namespace VideoIO;

namespace HumanInterface {
	class ScreenRecognizer {
		friend class ScreenCapture;
		
	public:
		ScreenRecognizer(Capture*);
		~ScreenRecognizer();
		
		void recognize();
		
	protected:
		Capture* m_camera;
		CvPoint2D32f* m_corners;
	
	private:
		Image* createChessboardImage(CvSize, int, int);
		CvPoint2D32f* findCornerPoints(const CvPoint2D32f*, int, int);
		void correctProportionalCornersOfScreen(CvPoint2D32f*, int, int);
		bool newFrameForRecognize(Image*);

		bool m_didRecognize;
	};
	
} // namespace HumanInterface

#endif //ScreenRecognizer_h
