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


#include "BackgroundSubtraction.h"

namespace OpenCV {
    
namespace Bitmap {

CodeBookSubstraction::CodeBookSubstraction()
    : m_codeBooksVector(CODEBOOK_RESOLUTION.width * CODEBOOK_RESOLUTION.height)
    , m_bounds(DEFAULT_BOUND)
    , m_channelsCount(CHANNELS_COUNT)
    , m_lastClearTime(clock())
{
}
    
CodeBookSubstraction::CodeBookSubstraction(const CodeBookSubstraction& cbs)
    : m_codeBooksVector(CODEBOOK_RESOLUTION.width * CODEBOOK_RESOLUTION.height)
    , m_bounds(cbs.m_bounds)
    , m_channelsCount(cbs.m_channelsCount)
    , m_lastClearTime(clock())
{
    int n = 0;
    if (cbs.m_codeBooksVector.size() == (CODEBOOK_RESOLUTION.width * CODEBOOK_RESOLUTION.height))
        foreach(codeBook, cbs.m_codeBooksVector) {
            foreach(entry, (*codeBook)) {
                CodeBookEntry* newEntry = new CodeBookEntry;
                *newEntry = *(*entry);
                m_codeBooksVector[n].push_back(newEntry);
            }
            n++;
        }
    assert(n == (CODEBOOK_RESOLUTION.width * CODEBOOK_RESOLUTION.height));
}

CodeBookSubstraction::CodeBookSubstraction(const Image* image, int channelsCount)
    : m_codeBooksVector(CODEBOOK_RESOLUTION.width * CODEBOOK_RESOLUTION.height)
    , m_bounds(DEFAULT_BOUND)
    , m_channelsCount(channelsCount)
    , m_lastClearTime(clock())
{
    learnBackground(image);
}

CodeBookSubstraction::~CodeBookSubstraction()
{
    foreach(codeBook, m_codeBooksVector) 
        foreach(entry, (*codeBook)) 
            delete (*entry);
}
    
void CodeBookSubstraction::learnBackground(const Image* image)
{
    Image* yuvImage = toYUV(image);
    yuvImage->resize(CODEBOOK_RESOLUTION);
    
    unsigned char* pixel = (unsigned char*)yuvImage->cvImage()->imageData;
    
    for (unsigned long p = 0
         ; p < (CODEBOOK_RESOLUTION.width * CODEBOOK_RESOLUTION.height)
         ; p++) {
        updateCodebook(&pixel[3 * p], m_codeBooksVector[p]);
        if ((clock() - m_lastClearTime) >= TIME_TO_ASUME_OBSOLETE)
            clearObsoleteEntries(m_codeBooksVector[p]);
    }
    if ((clock() - m_lastClearTime) >= TIME_TO_ASUME_OBSOLETE)
        m_lastClearTime = clock();
    delete yuvImage;
}

Mask* CodeBookSubstraction::subtractBackground(const Image* image)
{
    static int clearRate = CLEAR_RATE;
    Image* yuvImage = toYUV(image);
    yuvImage->resize(CODEBOOK_RESOLUTION);
    
    Mask* mask = new Image(CODEBOOK_RESOLUTION, UByte, 1);
    
    unsigned char* pixel = (unsigned char*)yuvImage->rawData();
    unsigned char* maskPixel = (unsigned char*)mask->rawData();
    
    bool doUpdate = ((clock() - m_lastClearTime) >= TIME_TO_ASUME_OBSOLETE);
    if (doUpdate) {
        m_lastClearTime = clock();
        clearRate--;
    }
    
    for (unsigned long p = 0
         ; p < (CODEBOOK_RESOLUTION.width * CODEBOOK_RESOLUTION.height)
         ; p++) {
        maskPixel[p] = diffPixel(&pixel[3 * p], m_codeBooksVector[p]);
        
        if (doUpdate) {
            updateCodebook(&pixel[3 * p], m_codeBooksVector[p]);
            if (!clearRate) {
                clearObsoleteEntries(m_codeBooksVector[p]);
                clearRate = CLEAR_RATE;
            }
        }
    }
    
    delete yuvImage;
    
    mask->resize(image->size(), Bilineal);
    return mask;
}
    
#ifdef DEBUG
Mask* CodeBookSubstraction::codeBookDepth()
{
    Mask* depth = new Image(CODEBOOK_RESOLUTION, UByte, 1);
    unsigned char* maskPixel = (unsigned char*)depth->rawData();
    
    for (unsigned long p = 0
         ; p < (CODEBOOK_RESOLUTION.width * CODEBOOK_RESOLUTION.height)
         ; p++) {
        maskPixel[p] = 8 * m_codeBooksVector[p].size() > 255 ? 255 : 8 * m_codeBooksVector[p].size();
    }
    return depth;
}
    
Image* CodeBookSubstraction::generateBackground()
{
    Image* background = new Image(CODEBOOK_RESOLUTION, UByte, 3);
    unsigned char* pixel = (unsigned char*)background->rawData();

    foreach(cb, m_codeBooksVector) {
        CodeBookEntry* backgroundEntry = (*cb)[0];
        foreach(entry, (*cb))
            if ((*entry)->timeOnScene > backgroundEntry->timeOnScene)
                backgroundEntry = (*entry);
        if (backgroundEntry)
            for (int i = 0; i < 3; i++)
                pixel[i] = (backgroundEntry->learnLow[i] >> 1) + (backgroundEntry->learnHigh[i] >> 1);
        pixel += 3;
    }
    background->convert(YUVToColor);
    return background;
}
#endif // DEBUG
    
unsigned char CodeBookSubstraction::diffPixel(unsigned char* pixel, CodeBook& cb)
{
    static long lastTime = clock();
    /* Find similar entry in the CodeBook */
    CodeBookEntry* foundEntry = NULL;
    
    /* Else only find entry */
    foreach(entry, cb) {
        int matchChannels = 0;
        for (int i = 0; i < m_channelsCount; i++) 
            if ((*entry)->learnHigh[i] >= pixel[i]
                && (*entry)->learnLow[i] <= pixel[i])
                matchChannels++;
        if (matchChannels == m_channelsCount 
            /* && (*entry)->timeOnScene >= (TIME_TO_ASUME_OBSOLETE >> 1) */ ) { /* Found */
            for (int i = 0; i < m_channelsCount; i++) {
                (*entry)->max[i] = (*entry)->max[i] < pixel[i] ? pixel[i] : (*entry)->max[i];
                (*entry)->min[i] = (*entry)->min[i] > pixel[i] ? pixel[i] : (*entry)->min[i];
            }
            foundEntry = *entry;
            break;
        }
    }
    if (foundEntry) {
        foundEntry->lastUpdate = clock();   /* Storage Times */
        foundEntry->timeOnScene += clock() - lastTime;
        lastTime = clock();
        return 0;
    }
    lastTime = clock();
    return 255;
}
    
CodeBookEntry* CodeBookSubstraction::updateCodebook(unsigned char* pixel, CodeBook& cb)
{
    static long lastTime = clock();
    int high[CHANNELS_COUNT];
    int low[CHANNELS_COUNT];
    for (int i = 0; i < m_channelsCount; i++) {
        high[i] = pixel[i] + m_bounds.val[i] > 255 ? 255 : pixel[i] + m_bounds.val[i];
        low[i] = pixel[i] - m_bounds.val[i] < 0 ? 0 : pixel[i] - m_bounds.val[i];
    }
    
    /* Find similar entry in the CodeBook */
    CodeBookEntry* foundEntry = NULL;
    foreach(entry, cb) {
        int matchChannels = 0;
        for (int i = 0; i < m_channelsCount; i++) 
            if ((*entry)->learnHigh[i] >= pixel[i]
                && (*entry)->learnLow[i] <= pixel[i])
                matchChannels++;
        if (matchChannels == m_channelsCount) { /* Found */
            for (int i = 0; i < m_channelsCount; i++) {
                (*entry)->max[i] = (*entry)->max[i] < pixel[i] ? pixel[i] : (*entry)->max[i];
                (*entry)->min[i] = (*entry)->min[i] > pixel[i] ? pixel[i] : (*entry)->min[i];
            }
            foundEntry = *entry;
            break;
        }
    }
    
    if (!foundEntry) {
        /* Create new entry if needed */
        foundEntry = new CodeBookEntry;
        for (int i = 0; i < m_channelsCount; i++) {
            foundEntry->learnHigh[i] = high[i];
            foundEntry->learnLow[i] = low[i];
            foundEntry->max[i] = pixel[i];
            foundEntry->min[i] = pixel[i];
            foundEntry->timeOnScene = 0;
        }
        cb.insert(cb.begin(), foundEntry);
    } else {
        /* Adjust bounds */
        for (int i = 0; i < m_channelsCount; i++) {
            if (foundEntry->learnHigh[i] < high[i])
                foundEntry->learnHigh[i]++;
            if (foundEntry->learnLow[i] > low[i])
                foundEntry->learnLow[i]--;
        }
    }
    
    assert(foundEntry);
    foundEntry->lastUpdate = clock();   /* Storage Times */
    foundEntry->timeOnScene += clock() - lastTime;
    lastTime = clock();
    return foundEntry;
}
    
long CodeBookSubstraction::clearObsoleteEntries(CodeBook& cb)
{
    long removedCount = 0;
    /* remove obsolete entries */
    //foreach(entry, cb) { /* Does not work with iterator */
    for (int i = 0; i < cb.size(); i++) {
        if ((clock() - cb[i]->lastUpdate) > ((TIME_TO_ASUME_OBSOLETE < cb[i]->timeOnScene) 
                                                ? cb[i]->timeOnScene 
                                                : TIME_TO_ASUME_OBSOLETE)) {
            CodeBookEntry* entryToRemove = cb[i];
            cb.erase(cb.begin() + i);
            delete entryToRemove; /* First remove from vector and after delete pointer */
            removedCount++;
        }
    }
    return removedCount;
}
    
} // namespace Bitmap
    
} // namespace OpenCV
