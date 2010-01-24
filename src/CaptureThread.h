/*-
 * Copyright (c) 2009 Ander Suarez and Endika Gutiérrez, University of Deusto
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
 *  \file CaptureThread.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 30/04/09
 */

#ifndef CaptureThread_h
#define CaptureThread_h

#include <QThread>
#include <QMutex>
//#include "OpenCV/Image.h"
#include "OpenCV/Capture.h"

using namespace OpenCV::VideoIO;
using namespace OpenCV::Bitmap;

const double DEFAULT_FPS = 24.97; /* Default fps for PAL video systems */

/**
 *  CaptureThread
 *  Creates thread for capture frame regularly.
 *  \threadsafe
 */
class CaptureThread : public QThread
{
public:
// Constructors
    /**
     *  Default Constructor
     *  \param  [in]    capture Pointer to Capture Source
     *  \param  [out]   handler Sets image's handler
     *  \param  [in]    fps     Frames per Sec to Capture
     */
    CaptureThread(const Capture&, Image*&, double = DEFAULT_FPS);
    virtual ~CaptureThread() { }

// Getters & Setters
    /**
     *  Sets capture's handler Image
     *  \return Pointer to handler
     */
    inline Image*& imageHandler() { return m_capturedImage; }

    /// Gets capturing fps
    inline double fps() { return m_fps; }
    inline void setFPS(double fps) { m_fps = fps; }

// Public Methods
    /// Starts Capturing
    inline void startCapturing() { if (!this->isRunning()) this->start(); }
    /// Stops Capturing
    inline void stopCapturing() { m_kill = true; }

protected:
// Protected Methods
    virtual void run();

    QMutex m_mutex;
    double m_fps;
    Capture m_capture;
    Image* m_capturedImage;

    bool m_kill;
};

#endif // CaptureThread_h
