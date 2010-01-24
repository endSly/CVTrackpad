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
 *  \file Mouse.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 19/02/09
 */

#ifndef Mouse_h
#define Mouse_h

#include <iostream>

#ifdef WIN32
#include <windows.h>
#endif

namespace Events {

#ifdef WIN32
    enum MouseButton {
        RightButton = MOUSEEVENTF_RIGHTDOWN,
        LeftButton = MOUSEEVENTF_LEFTDOWN,
        MiddleButton = MOUSEEVENTF_MIDDLEDOWN
    };
#endif

    enum MouseAction {
        ButtonDown = 0,
        ButtonUp = 1
    };

    class Mouse {
    public:
// Constructos
        virtual ~Mouse() { }//Destructor
        static Mouse* getInstance();

// Events
        /// Sends mouse clicks
        void click(int, int);
        /// Sends mouse movements
        void moveTo(int, int);

    protected:
// Protected Constructor
        Mouse() { }
};


} // namespace Events

#endif // Mouse_h
