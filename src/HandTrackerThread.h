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
 *  \file HandTrackerThread.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 10/06/09
 */

#ifndef HandTrackerThread_h
#define HandTrackerThread_h

#include <QThread>
#include <QMutex>

#include "OpenCV/OpenCV.hpp"
#include "Hand.h"

namespace HumanInterface {
    using namespace std;
    using namespace OpenCV;
    using namespace Tracking;
    using namespace Bitmap;

    /**
     *  Two threads
     *  One Searchs hand in scene
     *  and the other tracks this
     */
    class HandTrackerThread : public QThread {
    protected:
        /**
         *  Protected Class
         *  Tracks found hand
         */
        class TrackerThread : public QThread {
        public:
            TrackerThread(Image**);

            /// Safely trackers update
            inline void setTrackers(vector<Tracker*>* trackers) {
                if (m_trackers)
                    m_newTrackers = trackers;
                else
                    m_trackers = trackers;
            }

            /// QThreads default run function
            virtual void run();

            vector<Tracker*>* m_trackers;
            vector<Tracker*>* m_newTrackers;    // For safely trackers update

            Image** m_image;
            vector<CvConnectedComp*>* m_trackedHands;   // last tracked hands
            QMutex m_mutex;

            volatile bool m_kill;

        private:
            inline void updateTrackers() {
                foreach (tracker, (*m_trackers))
                  delete (*tracker);
                delete m_trackers; 
                m_trackers = m_newTrackers;
                m_newTrackers = NULL;
            }

        } m_trackerThread;

    public:
        /**
         *  Default Constructor
         *  \param  [in]    image       Image's delegate
         *  \param  [in]    handServer  Preloaded face classifier
         *  \param  [in]    cbs         CodeBookSubstraction for current Background
         */
        HandTrackerThread(Image*&, HandServer*, CodeBookSubstraction* = NULL);

        /// Stops thread
        virtual ~HandTrackerThread() { stopTracking(); updateHands(NULL); }

        /**  Gets last tracked hands
          *  \warning You migth need mutex here
          *  \return Last tracked CvConnectedComp
          */
        inline vector<CvConnectedComp*>* trackedHands() { return m_trackerThread.m_trackedHands; }
        /// \return Last tracked Face's rect
        inline CvRect faceRect() const { return m_handServer->faceRect(); }
        /**  Gets last tracked Hands
          *  \warning You migth need mutex here
          *  \return Vector of last tracked Hands
          */
        inline vector<Hand*>* hands() { return m_hands; }

        /// Start Threads
        inline void startTracking() { start();  m_trackerThread.start(); }

        /// Stop Threads
        inline void stopTracking() { m_trackerThread.m_kill = true; m_kill = true; }

    protected:
        /// Thread's function
        virtual void run();

        Image** m_image;
        HandServer* m_handServer;
        CodeBookSubstraction* m_cbs;
        vector<Hand*>* m_hands;     // Last found hands

        QMutex m_mutex;
        volatile bool m_kill;

    private:
        inline void updateHands(vector<Hand*>* newHands) {
            if (!m_hands) {
               m_hands = newHands;
               return;
            }

            /* Insert in last order if posible */
            /*
            for (int i = 0; i < newHands->size(); i++)
                for (int j = 0; j < m_trackerThread.m_trackedHands->size(); j++)
                    if ((*newHands)[i]->isOnRect(m_trackerThread.m_trackedHands->at(j)->rect)) {
                        if (j != i) {   // Swap hands at i and at j
                            Hand* temp = (*newHands)[i];
                            (*newHands)[i] = (*newHands)[j];
                            (*newHands)[j] = temp;
                        }
                        break;
                    }
            */
            /* Delete old and insert new */
            vector<Hand*>* old = m_hands;
            m_hands = newHands;
            foreach (hand, (*old))
                delete (*hand);
            delete old;
        }
    };

} // namespace HumanInterface

#endif // HandTrackerThread_h
