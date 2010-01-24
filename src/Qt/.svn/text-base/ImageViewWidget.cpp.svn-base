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


#include "ImageViewWidget.h"

namespace GUI {

ImageViewWidget::ImageViewWidget(QWidget* parent)
    : QWidget(parent)
    , m_imagelabel(new QLabel)
    , m_layout(new QVBoxLayout)
    , m_image(640, 480, QImage::Format_RGB32)
{
    m_layout->addWidget(m_imagelabel);

    // Fill image with black
    for (int x = 0; x < 640; x ++)
        for (int y =0; y < 480; y++)
            m_image.setPixel(x,y,qRgb(0, 0, 0));

    m_imagelabel->setPixmap(QPixmap::fromImage(m_image));
    setLayout(m_layout);
}

ImageViewWidget::~ImageViewWidget(void)
{
    delete m_layout;
    delete m_imagelabel;
}

void ImageViewWidget::setImageDelegate(Image*& image)
{
    if (image) {
        m_delegatedImage = &image;
        showImage(image);
        m_timerID = startTimer(50);
    }
}

void ImageViewWidget::showImage(Image* image)
{
    if (image->depth() != UByte) {
        std::cerr << "ImageViewWidget: Unexpected image depth\n";
        return;
    }

    unsigned char* imageData = (unsigned char*)image->rawData();
    if ((image->width() != m_image.width()) || (image->height() != m_image.height())) {
        QImage temp(image->width(), image->height(), QImage::Format_RGB32);
        m_image = temp;
    }

    switch (image->numberOfChannels()) {
    case 1:
        for(int j = 0; j < image->height(); j++)
            for(int i = 0; i < image->width(); i++) {
                m_image.setPixel(i, j, qRgb(imageData[0], imageData[0], imageData[0]));
                imageData++;
            }
        break;
    case 3:
        for(int j = 0; j < image->height(); j++)
            for(int i = 0; i < image->width(); i++){
                m_image.setPixel(i, j, qRgb(imageData[2], imageData[1], imageData[0]));
                imageData += 3;
            }
        break;
    default:
        std::cerr << "ImageViewWidget: Unexpected channels count\n";
        return;
    }
    m_imagelabel->setPixmap(QPixmap::fromImage(m_image));
}

void ImageViewWidget::timerEvent(QTimerEvent*)
{
    if (m_delegatedImage && *m_delegatedImage)
        showImage(*m_delegatedImage);
}

} // namespace GUI


