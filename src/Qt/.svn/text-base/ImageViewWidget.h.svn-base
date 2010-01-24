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
 *  \file ImageViewWidget.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 09/05/09
 */


#ifndef ImageViewWidget_h
#define ImageViewWidget_h

#include <iostream>

#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

#include <OpenCV/Image.h>

namespace GUI {
    using namespace OpenCV::Bitmap;

    class ImageViewWidget : public QWidget {
    Q_OBJECT
    public:
        ImageViewWidget(QWidget* parent = 0);
        virtual ~ImageViewWidget();

        void setImageDelegate(Image*&);

        void showImage(Image*);

        inline void stopRefresh() { killTimer(m_timerID); }

    protected:
        void timerEvent(QTimerEvent*);

        QLabel* m_imagelabel;
        QVBoxLayout* m_layout;
        QImage m_image;
        Image** m_delegatedImage;
        int m_timerID;
    };


} //namespace GUI

#endif // ImageViewWidget_h
