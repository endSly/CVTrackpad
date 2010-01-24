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

#include "MainWindow.h"
#include "ui_MainWindow.h"

const char* FACE_CASCADE_NAME = "../data/haarcascades/haarcascade_frontalface_default.xml";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_cbs(new CodeBookSubstraction)
    , m_handColor(NULL)
    , m_faceClassifier(NULL)
    , ui(new Ui::MainWindow)
    , m_systemTray(new GUI::TrayIcon)
    , m_mouse(Events::Mouse::getInstance())
    , m_bootScreen(new StartScreen)
    , m_cameraDeviceDialog(new CameraDeviceDialog)
    , m_aboutScreen(new AboutScreen)
{
    //QApplication::setQuitOnLastWindowClosed(true);
    // Shold be initialized after setupUI
    ui->setupUi(this);
    hide();

    // Show introduction screen
    m_bootScreen->show();

    m_bootScreen->setString("Creando el interfaz...");

    this->createActions();
    this->connectSignals();

      // Create system tray icon
    this->createMenu();
    m_systemTray->enableIcon();

    m_imageWidget = new GUI::ImageViewWidget(ui->cameraContainer);

    try {
        m_bootScreen->setString("Abriendo la C�mara...");
        // Try to open Camera device
        m_camera = new Camera(DEFAULT_CAMERA);

        m_bootScreen->setString("Cargando la Cascada de Haar...");
        // Try to open haar cascade
        m_faceClassifier = new HaarClassifier(FACE_CASCADE_NAME);
    } catch (DeviceNotFoundException& ex) {
        std::cerr << ex;
        QMessageBox::critical(this,
                              tr("No se pudo abrir el Dispositivo de Video"),
                              tr("No se encontro ningun dispositivo de entrada de video. "
                                 " Es posible que el dispositivo este previamente abierto o no "
                                 "se encuentre disponible."));
    } catch (FileNotFoundException& ex) {
        std::cerr << ex;
        QMessageBox::critical(this,
                              tr("Error cargando la Cascada de Haar"),
                              tr("No se pudo abrir la cascada de Haar necesaria. "
                                 "La reinstalaci�n del programa deber�a solucionar el problema."));
        /*
         *  Here histogram should be asked
         */
        delete m_camera;
    }

    m_bootScreen->setString("Inicializando la Captura...");
    m_captureThread = new CaptureThread(*m_camera, m_image);

    m_bootScreen->setString("Inicializando el seguimiento...");
    m_handServer = new HandServer(m_faceClassifier);
    m_handTracking = new HandTrackerThread(m_image, m_handServer, m_cbs);
    m_handTracking->startTracking();
    QMainWindow::startTimer(50);

    // Close booting screen and show succesfully message

    m_bootScreen->setString("Listo.");
    this->statusBar()->showMessage("Listo.", 9000);

    m_bootScreen->close();
    this->show();
}

MainWindow::~MainWindow()
{
    QMutex mutex;
    mutex.lock();

    m_handTracking->stopTracking();
    m_captureThread->stopCapturing();

    /* delete UI while threads are deleted */
    //m_imageWidget->stopRefresh();
    delete m_imageWidget;
    delete m_cameraDeviceDialog;
    delete m_bootScreen;
    delete m_aboutScreen;
    delete ui;

    /* Now, if threads are no killed yet, wait */
    while (!m_captureThread->isFinished()) { }
    while (!m_handTracking->isFinished()) { }

    /* Now everything can be safely deleted */
    delete m_captureThread;
    delete m_handTracking;

    delete m_cbs;
    delete m_handColor;
    delete m_faceClassifier;

    //delete m_image;   // This will crash!!
    //delete m_camera;

    mutex.unlock();
}

void MainWindow::timerEvent(QTimerEvent*)
{
    DrawableImage* drawedImage = static_cast<DrawableImage*> (m_image->clone());
    drawedImage->drawRectangle(m_handTracking->faceRect(), 3, COLOR_GREEN);

    vector<CvConnectedComp*>* trackedHands = m_handTracking->trackedHands();
    for (int i = 0; i < trackedHands->size() && (*trackedHands)[i]; i++)
        drawedImage->drawRectangle((*trackedHands)[i]->rect, 3, COLORS_TO_DRAW_HANDS[i % 4]);

    drawedImage->flip();
    m_imageWidget->showImage(drawedImage);
    delete drawedImage;
}

// Private functions

void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    QMainWindow::connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    QMainWindow::connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), this);
    QMainWindow::connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    QMainWindow::connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::createMenu()
{
    m_iconMenu = new QMenu(this);
    m_iconMenu->addAction(minimizeAction);
    m_iconMenu->addAction(maximizeAction);
    m_iconMenu->addAction(restoreAction);
    m_iconMenu->addSeparator();
    m_iconMenu->addAction(quitAction);

    m_systemTray->setMenu(m_iconMenu);
}

void MainWindow::connectSignals()
{
    // Connect Buttons Signals
    connect(ui->learningButton, SIGNAL(clicked()), this, SLOT(learn_button_clicked()));
    connect(ui->exeButton, SIGNAL(clicked()), this, SLOT(exe_button_clicked()));
    
    // Connect Main Menu Signals
    connect(ui->actionSalir, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionFuente, SIGNAL(triggered()), this, SLOT(action_Fuente_clicked()));
    connect(ui->actionAprender_fondo, SIGNAL(triggered()), this, SLOT(learn_button_clicked()));
    connect(ui->actionAcerca_de_CVTrackpad, SIGNAL(triggered()), this, SLOT(action_About_clicked()));

    // Connect miscelaneus Signals
    connect(this->m_cameraDeviceDialog, SIGNAL(getValueSignal()), this, SLOT(select_Device()));
}


// Private Slots

void MainWindow::on_mouseTestButton_clicked()
{
    for (int i = 0; i < 80000; i++)
        m_mouse->moveTo(i / 100, i / 100);
    qDebug() << m_device;
    //m_mouse->click(Mouse::ButtonDown, Mouse::LeftButton);
}


void MainWindow::action_Fuente_clicked()
{
    //Camera* newCamera;
    m_cameraDeviceDialog->show();
    /*
    m_device = m_cameraDeviceDialog->getValue();
    try {
        newCamera = new Camera(m_device);
    } catch (DeviceNotFoundException& ex) {
        std::cerr << ex;
        QMessageBox::critical(this,
                              tr("No se pudo abrir el Dispositivo de Video"),
                              tr("No se abrir la entrada de video seleccionada."
                                 "Es posible que ya se encuentre abierta o no exista."));
    }
    m_camera = newCamera;
    */
}

void MainWindow::select_Device()
{
}

void MainWindow::learn_button_clicked()
{
    QMessageBox::information(this, 
                             tr("Aprendiendo fondo"),
                             tr("Por favor, permanezca 4 segundos fuera de la pantalla"));
    this->statusBar()->showMessage("Aprendiendo fondo...", 4);
    for (long time = clock() + (4 * CLOCKS_PER_SEC) ; clock() <= time; )
        m_cbs->learnBackground(m_image);
}

void MainWindow::exe_button_clicked()
{
    hide();
}

void MainWindow::action_About_clicked()
{
    m_aboutScreen->show();
}
