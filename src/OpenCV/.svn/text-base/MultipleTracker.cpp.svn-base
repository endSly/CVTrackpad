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


#include "MultipleTracker.h"


namespace OpenCV {
    
namespace Tracking {

MultipleTracker::MultipleTracker()
    : m_trackers(NULL)
{
}
    
MultipleTracker::MultipleTracker(const MultipleTracker& mt)
    : m_trackers(mt.m_trackers)
{
}
    
MultipleTracker::MultipleTracker(std::vector <Tracker*>* trackers)
    : m_trackers(trackers)
{
}
    
MultipleTracker::~MultipleTracker()
{
#pragma omp parallel for
    foreach (tracker, (*m_trackers))
        delete (*tracker);
}

void MultipleTracker::startTracking(const Image* image, const CvConnectedComp* connectedComps)
{
#pragma omp parallel for
    foreach (tracker, (*m_trackers))
        (*tracker)->startTracking(image, connectedComps);

}

CvConnectedComp* MultipleTracker::track(const Image* image)
{
    if (!m_trackers || !m_trackers->size())
        return NULL;
    
    CvRect rects[m_trackers->size()];

    unsigned int i = 0;
#pragma omp parallel for
    foreach (tracker, (*m_trackers))
        rects[i++] = (*tracker)->track(image)->rect;

    assert(i == m_trackers->size());
        
    CvConnectedComp* rectComp = new CvConnectedComp;
    rectComp->rect = defaultRect(rects, m_trackers->size());
    return rectComp;
    
}
    
CvRect MultipleTracker::defaultRect(CvRect* rects, int count)
{
    assert(count);
        
    CvRect defRect;
    defRect.x = 0;
    defRect.y = 0;
    defRect.width = 0;
    defRect.height = 0;
        
    for (int i = 0; i < count; i++) {
        defRect.x += rects[i].x;
        defRect.y += rects[i].y;
        defRect.width += rects[i].width;
        defRect.height += rects[i].height;
    }
        
    defRect.x /= count;
    defRect.y /= count;
    defRect.width /= count;
    defRect.height /= count;
        
    return defRect;
}
    
} // namespace Tracking
    
} // namespace OpenCV




