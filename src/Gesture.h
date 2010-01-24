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
 *  \file Gesture.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 07/05/09
 */

#ifndef Gesture_h
#define Gesture_h

#include <math.h>
#include <queue>

#include <QThread>
#include <QEvent>

#include "Macros.h"
//#include "OpenCV/OpticalObject.h"
#include "Hand.h"

namespace HumanInterface {
    using namespace OpenCV::VectorizedGraphics;

    enum Type {
        None = 0,
        Close = 1000,   /* User's QEvents space */
        Open = 1001,
        Drag = 1002
    };

    const int GESTURE_QUEUE_LEN = 32;
    const int GESTURE_QUEUE_MIN_TO_EVALUATE = 8;

    /// Stores Geture Event's code
    class GestureEvent : public QEvent {
    public:
        GestureEvent(int type) : QEvent((QEvent::Type)type) { }
    };

    /**
     *  GestureServer
     *  Creates thread to observe OpticalObject's evolution and
     *  interpret gestures.
     *  \threadsafe
     *  \todo
     */
    class GestureServer : public QThread {
    public:
        GestureServer();
        GestureServer(const GestureServer&);
        /**
         *  Default Constructor
         *  \param  [in]    observer    CvConnectedCompenents to be looked into
         *  \param  [in]    handler     Event's handler
         */
        GestureServer(OpticalObject*&, QObject&);
        virtual ~GestureServer();

        /// \return Object to be observed
        inline OpticalObject*& observer() { return *m_objectToObserve; }
        /// \return Event's handler
        inline QObject& eventHandler() { return *m_eventHandler; }
        /// Sets object to be observe
        inline void setObserver(OpticalObject*& optObj) { m_objectToObserve = &optObj; }
        /// Sets event's handler
        inline void setEventHandler(QObject& handler) { m_eventHandler = &handler; }

    protected:
        virtual void run();

        QObject* m_eventHandler;
        OpticalObject** m_objectToObserve;
        std::vector<double> m_lastAreas;

    private:
        void areaStats(double&, double&);

        bool m_killed; // QThread can not be killed externally
    };

} // namespace HumanInterface

#endif // Gesture_H
