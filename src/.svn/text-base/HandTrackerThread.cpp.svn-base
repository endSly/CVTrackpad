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


#include "HandTrackerThread.h"

namespace HumanInterface {

/* class TrackerThread */

HandTrackerThread::TrackerThread::TrackerThread(Image** image)
    : QThread()
    , m_trackers(NULL)
    , m_newTrackers(NULL)
    , m_image(image)
    , m_trackedHands(new vector<CvConnectedComp*>(MAX_HANDS_TO_TRACK))
    , m_kill(false)
{
    foreach (tracked, (*m_trackedHands))    // Clean up vector
        (*tracked) = NULL;
}

void HandTrackerThread::TrackerThread::run()
{
    for (; !(volatile bool)m_kill; ) {
        assert(m_image);
        if ((volatile void*)!m_trackers)
            continue;
        assert(*m_image);

        if (m_newTrackers)     // We have new tracker waiting
            updateTrackers();

        Image* trackingImage = (*m_image)->clone();
        int i;
#pragma omp parallel for shared(trackingImage) private(i)
        for (i = 0; i < m_trackers->size(); i++) { // Track each hand
            cvReleaseConnectedComp((*m_trackedHands)[i]);
            if ((*m_trackers)[i])
                (*m_trackedHands)[i] = (*m_trackers)[i]->track(trackingImage);
        }

        delete trackingImage;
    }
    m_kill = false;
    this->exit();
}

/* class HandTrackerThread */

HandTrackerThread::HandTrackerThread(Image*& image, HandServer* handServer, CodeBookSubstraction* cbs)
    : m_trackerThread(&image)
    , m_image(&image)
    , m_handServer(handServer)
    , m_cbs(cbs)
    , m_hands(NULL)
    , m_kill(false)
{
}

void HandTrackerThread::run()
{
    while (!(volatile bool)m_kill) {
        Image* image = (*m_image)->clone();
        Mask* backgroundSubsMask = m_cbs ? m_cbs->subtractBackground(image) : NULL; // Get Background
        vector<Hand*>* hands = m_handServer->findAllHands(image, backgroundSubsMask);  // Find hand

        if (hands && hands->size()) {   // One or more hands found
            // Delete and update with new hands
            updateHands(hands);
            // Creates tracker for each hand
            vector<Tracker*>* trackers = new vector<Tracker*>(m_hands->size());
            int i;
#pragma omp parallel for private(i) shared(m_hands, trackers)
            for (i = 0; i < m_hands->size()/* && (*hands)[i]*/; i++)
                (*trackers)[i] = ((*m_hands)[i]->handTracker<MeanShift>(image));    // Mean Shift is one of the fastest
                                                                                    // tracking algorithm
            m_trackerThread.setTrackers(trackers);
        }

        delete backgroundSubsMask;
        delete image;
    }
    m_kill = false;
    this->exit();
}

} // namespace HumanInterface
