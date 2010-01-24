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
 *  \file MainWindow.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 21/12/08
 */

#ifndef MainWindow_h
#define MainWindow_h

#include "time.h"

//#include <QThread>
#include <QtGui/QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>

#include "ImageViewWidget.h"
#include "TrayIcon.h"
#include "Mouse.h"
#include "StartScreen.h"
#include "AboutScreen.h"

//#include "OpenCV/OpenCV.hpp"

#include "HandTrackerThread.h"
#include "CaptureThread.h"
#include "CameraDeviceDialog.h"
#include "VideoWriter.h"

#include "config.h"

namespace Ui {
    class MainWindow;
}

using namespace OpenCV;
using namespace OpenCV::Tracking;
using namespace OpenCV::VideoIO;
using namespace OpenCV::VectorizedGraphics;
using namespace HumanInterface;

const CvScalar COLORS_TO_DRAW_HANDS[] = {COLOR_BLUE, COLOR_RED, COLOR_BLACK, COLOR_WHITE};

/**
 *  MainWindow
 *  Implememntation of main window class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     *  Default Constructor
     *  \param  [in]    parent  Parent Widget
     */
    MainWindow(QWidget* = 0);

    /// Deletes Window. Called when window closed
    virtual ~MainWindow();

protected:
    void timerEvent(QTimerEvent*);

    /* For hand tracking*/
    Camera* m_camera;

    CaptureThread* m_captureThread;
    CodeBookSubstraction* m_cbs;

    HandTrackerThread* m_handTracking;
    Histogram* m_handColor;
    HaarClassifier* m_faceClassifier;
    HandServer* m_handServer;

    Image* m_image;


private:
    void createActions();
    void createMenu();
    void connectSignals();

    Ui::MainWindow *ui;
    GUI::ImageViewWidget* m_imageWidget;
    GUI::TrayIcon* m_systemTray;
    Events::Mouse* m_mouse;
    QMenu* m_iconMenu;
    StartScreen* m_bootScreen;
    CameraDeviceDialog* m_cameraDeviceDialog;
    int m_device;
    AboutScreen* m_aboutScreen;


    QAction* minimizeAction;
    QAction* maximizeAction;
    QAction* restoreAction;
    QAction* quitAction;

private slots:
    void on_mouseTestButton_clicked();
    void action_Fuente_clicked();
    void action_About_clicked();
    void exe_button_clicked();
    void learn_button_clicked();
    void select_Device();

};

#endif // MainWindow_h
