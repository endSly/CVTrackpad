# -------------------------------------------------
# Project created by QtCreator 2009-05-10T13:56:02
# -------------------------------------------------
QT -= gui
TARGET = Engine
TEMPLATE = lib
DEFINES += ENGINE_LIBRARY
SOURCES += engine.cpp \
    ScreenRecognizer.cpp \
    ScreenCapture.cpp \
    main.cpp \
    Hand.cpp \
    Gesture.cpp \
    CaptureThread.cpp
HEADERS += engine.h \
    Engine_global.h \
    CaptureThread.h \
    ScreenRecognizer.h \
    ScreenCapture.h \
    Hand.h \
    Gesture.h
