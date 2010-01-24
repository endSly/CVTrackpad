# -------------------------------------------------
# Project created by QtCreator 2009-05-12T14:20:08
# -------------------------------------------------
TARGET = CVTrackpad
TEMPLATE = app
SOURCES += MainWindow.cpp \
    src/Qt/TrayIcon.cpp \
    src/Qt/UIs/StartScreen.cpp \
    src/ScreenRecognizer.cpp \
    src/ScreenCapture.cpp \
    src/Hand.cpp \
    src/Gesture.cpp \
    src/CaptureThread.cpp \
    src/OpenCV/VideoWriter.cpp \
    src/OpenCV/VideoCapture.cpp \
    src/OpenCV/QueuedTracking.cpp \
    src/OpenCV/ProcessableImage.cpp \
    src/OpenCV/OpticalObject.cpp \
    src/OpenCV/OpticalFlowLK.cpp \
    src/OpenCV/OFLKTracker.cpp \
    src/OpenCV/ObjectTracker.cpp \
    src/OpenCV/MultipleTracker.cpp \
    src/OpenCV/MeanShift.cpp \
    src/OpenCV/Image.cpp \
    src/OpenCV/Histogram.cpp \
    src/OpenCV/HaarClassifier.cpp \
    src/OpenCV/Estimator.cpp \
    src/OpenCV/DrawableImage.cpp \
    src/OpenCV/Capture.cpp \
    src/OpenCV/CAMShift.cpp \
    src/OpenCV/Camera.cpp \
    src/OpenCV/BackgroundSubtraction.cpp \
    main.cpp \
    src/Events/Mouse.cpp \
    src/Qt/ImageViewWidget.cpp \
    src/Qt/UIs/CameraDeviceDialog.cpp \
    src/Qt/UIs/SetCornerScreen.cpp \
    src/Qt/UIs/AboutScreen.cpp \
    src/HandTrackerThread.cpp
HEADERS += MainWindow.h \
    src/Qt/TrayIcon.h \
    src/Qt/UIs/StartScreen.h \
    src/ScreenRecognizer.h \
    src/ScreenCapture.h \
    src/Hand.h \
    src/Gesture.h \
    src/CaptureThread.h \
    src/OpenCV/VideoWriter.h \
    src/OpenCV/VideoCapture.h \
    src/OpenCV/Tracker.h \
    src/OpenCV/QueuedTracking.h \
    src/OpenCV/ProcessableImage.h \
    src/OpenCV/OpticalObject.h \
    src/OpenCV/OpticalFlowLK.h \
    src/OpenCV/OpticalFlow.h \
    src/OpenCV/OpenCV.hpp \
    src/OpenCV/OFLKTracker.h \
    src/OpenCV/ObjectTracker.h \
    src/OpenCV/MultipleTracker.h \
    src/OpenCV/MeanShift.h \
    src/OpenCV/Image.h \
    src/OpenCV/Histogram.h \
    src/OpenCV/HaarClassifier.h \
    src/OpenCV/Estimator.h \
    src/OpenCV/DrawableImage.h \
    src/OpenCV/Capture.h \
    src/OpenCV/CAMShift.h \
    src/OpenCV/Camera.h \
    src/OpenCV/BackgroundSubtraction.h \
    src/OpenCV/include/OpenCV.h \
    src/OpenCV/include/Macros.h \
    src/OpenCV/include/ExternalBundle.h \
    src/OpenCV/include/Exception.h \
    src/Events/Mouse.h \
    src/Qt/ImageViewWidget.h \
    src/Qt/UIs/CameraDeviceDialog.h \
    src/Qt/UIs/SetCornerScreen.h \
    src/Qt/UIs/AboutScreen.h \
    src/HandTrackerThread.h
INCLUDEPATH += ./src/Qt \
    ./src/Qt/UIs \
    ./src/Events \
    ./src \
    ./src/include \
    ./src/OpenCV \
    ./src/OpenCV/include
FORMS += MainWindow.ui \
    src/Qt/UIs/StartScreen.ui \
    src/Qt/UIs/CameraDeviceDialog.ui \
    src/Qt/UIs/SetCornerScreen.ui \
    src/Qt/UIs/AboutScreen.ui
win32 { 
    LIBS += -L"../../../../../../../Archivos de programa/OpenCV/otherlibs/_graphics/lib" \
        -L"../../../../../../../Archivos de programa/OpenCV/lib" \
        -lcv \
        -lcvaux \
        -lcxcore \
        -lhighgui
    INCLUDEPATH += C:/ARCHIV~1/OpenCV/cvaux/include \
        C:/ARCHIV~1/OpenCV/cv/include \
        C:/ARCHIV~1/OpenCV/cxcore/include \
        C:/ARCHIV~1/OpenCV/otherlibs/highgui \
        C:/ARCHIV~1/OpenCV/ml/include
    DEFINES += WIN32
}
unix { 
    INCLUDEPATH += /usr/include/opencv
    INCLUDEPATH += /usr/include
    LIBS += /usr/lib/libcv.so \
        /usr/lib/libcvaux.so \
        /usr/lib/libhighgui.so
    DEFINES += UNIX
}
RESOURCES += CVTrackPadResource.qrc
OBJECTS_DIR += ./src/build
DESTDIR = ./build
RC_FILE += icon.rc
