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
 *  \file ExternalBundle.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 03/03/09
 */

#ifndef ExternalBundle_h
#define ExternalBundle_h

#ifdef MAC_OS_X

#include "CoreFoundation/CoreFoundation.h"

#define DEFAULT_PATH_LEN 2048

//inline char* getBundle(const char* resourceName, const char* resourceType)
#define GET_BUNDLE(resourceName, resourceType) 
{
    // (this is the mac way to package application resources)
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourceURL(mainBundle, 
                                                    CFSTR(resourceName), 
                                                    CFSTR(resourceType),
                                                    NULL);
    char* path = new char[DEFAULT_PATH_LEN];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, 
                                          TRUE, 
                                          reinterpret_cast<UInt8*> (path), 
                                          DEFAULT_PATH_LEN)) {
        delete path;
        CFRelease(resourcesURL);
        return NULL;
    }
    CFRelease(resourcesURL);
    return path;
}

#endif // MAC_OS_X


#endif // ExternalBundle_h



