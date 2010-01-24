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
 *  \file TrayIcon.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 21/12/08
 */

#ifndef TrayIcon_h
#define TrayIcon_h

#include <QSystemTrayIcon>
#include <QDialog>
#include <QIcon>
#include <QPixmap>
#include <QMenu>

QT_BEGIN_NAMESPACE
class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;
QT_END_NAMESPACE

//! [0]

namespace GUI {

class TrayIcon: public QObject
{
    Q_OBJECT

public:

    TrayIcon();
    /// Adds a context menu to the SystemTrayIcon
    void setMenu(QMenu* menu);
    /// Put SystemTrayIcon in operative mode
    void enableIcon();

protected:

private slots:


private:
    void createActions();

    QSystemTrayIcon* m_sysTrayIcon;
    QIcon* m_icon;
    QPixmap* m_pixmapImage;
    QMenu* m_TrayIconMenu;


};

} // namespace GUI


#endif
