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


#include "Gesture.h"

namespace HumanInterface {

GestureServer::GestureServer()
    : QThread()
    , m_lastAreas(GESTURE_QUEUE_LEN)
    , m_killed(false)
{
}

GestureServer::GestureServer(const GestureServer& gs)
    : QThread() /* No copy constructor for QThread */
    , m_eventHandler(gs.m_eventHandler)
    , m_objectToObserve(gs.m_objectToObserve)
    , m_lastAreas(GESTURE_QUEUE_LEN)
    , m_killed(false)
{
}

GestureServer::GestureServer(OpticalObject*& object, QObject& handler)
    : QThread()
    , m_eventHandler(&handler)
    , m_objectToObserve(&object)
    , m_lastAreas(GESTURE_QUEUE_LEN)
    , m_killed(false)
{
}

GestureServer::~GestureServer()
{
    m_killed = true;    // Send kill msg
    while (this->isRunning()) { }
}

void GestureServer::run()
{
    while (!(volatile bool)m_killed) {
        if (!m_objectToObserve || !*m_objectToObserve) {
            msleep(100);    // Not sature thread
            continue;
        }

        double currentArea = (*m_objectToObserve)->area();
        if (m_lastAreas.size() < GESTURE_QUEUE_MIN_TO_EVALUATE) {
            double average, desviationAverage;
            areaStats(average, desviationAverage);
            if (abs(average - currentArea) > desviationAverage) {
                // We have an event

            }
        }

        if (m_lastAreas.size() >= GESTURE_QUEUE_LEN)
            ;
        msleep(75);
    }
}

void GestureServer::areaStats(double& average, double& desviationAverage)
{
    average = 0;
    desviationAverage = 0;
    if (!m_lastAreas.size())
        return;

    foreach (value, m_lastAreas)
        average += (*value);
    average /= m_lastAreas.size();

    foreach (value, m_lastAreas)
        desviationAverage += fabs((*value) - average);
    desviationAverage /= m_lastAreas.size();
}

} // namespace HumanInterface
