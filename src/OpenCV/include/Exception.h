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
 *  \file Exception.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 08/04/09
 */

#ifndef Exception_h
#define Exception_h

#include <iostream>
#include <exception>
#include <string>

#include "string.h"

namespace OpenCV {
    /**
     *  FileNotFoundException
     *  Excepcion if file can't be opened
     */
    class FileNotFoundException : public std::exception {
    public:
        FileNotFoundException() : m_filename(strcpy(new char[8], "unknown")) { }
        FileNotFoundException(const FileNotFoundException& ex) : m_filename(strcpy(new char[strlen(ex.m_filename)], ex.m_filename)) {  }
        FileNotFoundException(const char* filename) : m_filename(strcpy(new char[strlen(filename)], filename)) {  }
        virtual ~FileNotFoundException() throw () { delete m_filename; }
        
        inline char* filename() const { return m_filename; }
        
        friend std::ostream& operator<<(std::ostream& os, const FileNotFoundException& ex) { return os << "File not Found: " << ex.filename() << "\n"; }
        
    protected:
        char* m_filename;
    };
    
    /**
     *  DeviceNotFoundException
     *  Exception if Device not exists or is already opened.
     */
    class DeviceNotFoundException : public std::exception {
    public:
        DeviceNotFoundException() : m_deviceID(-1) { }
        DeviceNotFoundException(const DeviceNotFoundException& ex) : m_deviceID(ex.m_deviceID) { }
        DeviceNotFoundException(int device) : m_deviceID(device) {  }
        virtual ~DeviceNotFoundException() throw () { }
        
        inline int deviceID() const { return m_deviceID; }
        
        friend std::ostream& operator<<(std::ostream& os, const DeviceNotFoundException& ex) { return os << "Device not found or already opened: DeviceID=" << ex.deviceID() << "\n"; }
        
    protected:
        int m_deviceID;
    };
} // namespace OpenCV

#endif // Exception_h

