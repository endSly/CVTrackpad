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

#ifndef OpenCV_h
#define OpenCV_h

#define DEBUG

//  I think that only Mac OS X cleans memory before reassign.
//#define SKIP_CLEAR

//#include <cxcore.h>  // included by cv.h, ml.h and highgui.h
//#include <cv.h>      // included by cvaux.h
#include <cvaux.h>
#include <ml.h>
#include <highgui.h>

/// OpenCV's iterative algorthim's termination criteria
enum TerminationCriteria {
    Itertion = CV_TERMCRIT_ITER,    /* Iterate n-times */
    Epsilon = CV_TERMCRIT_EPS,      /* Iterate until error < epsilon */
    EpsilonWithMaxIter = CV_TERMCRIT_ITER | CV_TERMCRIT_EPS     /* Iterate n-times or until error < epsilon */
};

/**
 * Releases CvConnectedComp
 *  I miss this function from OpenCV. It's useful and
 *  else may be confusious
 */
inline void cvReleaseConnectedComp(CvConnectedComp*&) {
    //if (cc->contour)
    //    cvReleaseMemStorage(&(cc->contour->storage));   // First release allocated memory
    //delete cc; // then release struct
}

#endif // OpenCV_h
