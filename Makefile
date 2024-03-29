#############################################################################
# Makefile for building: build/CVTrackpad
# Generated by qmake (2.01a) (Qt 4.5.1) on: Mon Jun 15 10:46:21 2009
# Project:  CVTrackpad.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/share/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o Makefile CVTrackpad.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DUNIX -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt/mkspecs/linux-g++-64 -I. -I/usr/include/QtCore -I/usr/include/QtGui -I/usr/include -Isrc/Qt -Isrc/Qt/UIs -Isrc/Events -Isrc -Isrc/include -Isrc/OpenCV -Isrc/OpenCV/include -I/usr/include/opencv -I/usr/include -I. -I.
LINK          = g++
LFLAGS        = -m64
LIBS          = $(SUBLIBS)  -L/usr/lib /usr/lib/libcv.so /usr/lib/libcvaux.so /usr/lib/libhighgui.so -lQtGui -L/usr/lib -L/usr/X11R6/lib64 -pthread -lpng -lfreetype -lgobject-2.0 -lSM -lICE -pthread -pthread -lXrender -lfontconfig -lXext -lX11 -lQtCore -lz -lm -pthread -lgthread-2.0 -lrt -lglib-2.0 -ldl -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = src/build/

####### Files

SOURCES       = MainWindow.cpp \
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
		src/HandTrackerThread.cpp moc_MainWindow.cpp \
		moc_TrayIcon.cpp \
		moc_StartScreen.cpp \
		moc_ImageViewWidget.cpp \
		moc_CameraDeviceDialog.cpp \
		moc_SetCornerScreen.cpp \
		moc_AboutScreen.cpp \
		qrc_CVTrackPadResource.cpp
OBJECTS       = src/build/MainWindow.o \
		src/build/TrayIcon.o \
		src/build/StartScreen.o \
		src/build/ScreenRecognizer.o \
		src/build/ScreenCapture.o \
		src/build/Hand.o \
		src/build/Gesture.o \
		src/build/CaptureThread.o \
		src/build/VideoWriter.o \
		src/build/VideoCapture.o \
		src/build/QueuedTracking.o \
		src/build/ProcessableImage.o \
		src/build/OpticalObject.o \
		src/build/OpticalFlowLK.o \
		src/build/OFLKTracker.o \
		src/build/ObjectTracker.o \
		src/build/MultipleTracker.o \
		src/build/MeanShift.o \
		src/build/Image.o \
		src/build/Histogram.o \
		src/build/HaarClassifier.o \
		src/build/Estimator.o \
		src/build/DrawableImage.o \
		src/build/Capture.o \
		src/build/CAMShift.o \
		src/build/Camera.o \
		src/build/BackgroundSubtraction.o \
		src/build/main.o \
		src/build/Mouse.o \
		src/build/ImageViewWidget.o \
		src/build/CameraDeviceDialog.o \
		src/build/SetCornerScreen.o \
		src/build/AboutScreen.o \
		src/build/HandTrackerThread.o \
		src/build/moc_MainWindow.o \
		src/build/moc_TrayIcon.o \
		src/build/moc_StartScreen.o \
		src/build/moc_ImageViewWidget.o \
		src/build/moc_CameraDeviceDialog.o \
		src/build/moc_SetCornerScreen.o \
		src/build/moc_AboutScreen.o \
		src/build/qrc_CVTrackPadResource.o
DIST          = /usr/share/qt/mkspecs/common/g++.conf \
		/usr/share/qt/mkspecs/common/unix.conf \
		/usr/share/qt/mkspecs/common/linux.conf \
		/usr/share/qt/mkspecs/qconfig.pri \
		/usr/share/qt/mkspecs/features/qt_functions.prf \
		/usr/share/qt/mkspecs/features/qt_config.prf \
		/usr/share/qt/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt/mkspecs/features/default_pre.prf \
		/usr/share/qt/mkspecs/features/debug.prf \
		/usr/share/qt/mkspecs/features/default_post.prf \
		/usr/share/qt/mkspecs/features/warn_on.prf \
		/usr/share/qt/mkspecs/features/qt.prf \
		/usr/share/qt/mkspecs/features/unix/thread.prf \
		/usr/share/qt/mkspecs/features/moc.prf \
		/usr/share/qt/mkspecs/features/resources.prf \
		/usr/share/qt/mkspecs/features/uic.prf \
		/usr/share/qt/mkspecs/features/yacc.prf \
		/usr/share/qt/mkspecs/features/lex.prf \
		/usr/share/qt/mkspecs/features/include_source_dir.prf \
		CVTrackpad.pro
QMAKE_TARGET  = CVTrackpad
DESTDIR       = build/
TARGET        = build/CVTrackpad

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_MainWindow.h ui_StartScreen.h ui_CameraDeviceDialog.h ui_SetCornerScreen.h ui_AboutScreen.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) build/ || $(MKDIR) build/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: CVTrackpad.pro  /usr/share/qt/mkspecs/linux-g++-64/qmake.conf /usr/share/qt/mkspecs/common/g++.conf \
		/usr/share/qt/mkspecs/common/unix.conf \
		/usr/share/qt/mkspecs/common/linux.conf \
		/usr/share/qt/mkspecs/qconfig.pri \
		/usr/share/qt/mkspecs/features/qt_functions.prf \
		/usr/share/qt/mkspecs/features/qt_config.prf \
		/usr/share/qt/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt/mkspecs/features/default_pre.prf \
		/usr/share/qt/mkspecs/features/debug.prf \
		/usr/share/qt/mkspecs/features/default_post.prf \
		/usr/share/qt/mkspecs/features/warn_on.prf \
		/usr/share/qt/mkspecs/features/qt.prf \
		/usr/share/qt/mkspecs/features/unix/thread.prf \
		/usr/share/qt/mkspecs/features/moc.prf \
		/usr/share/qt/mkspecs/features/resources.prf \
		/usr/share/qt/mkspecs/features/uic.prf \
		/usr/share/qt/mkspecs/features/yacc.prf \
		/usr/share/qt/mkspecs/features/lex.prf \
		/usr/share/qt/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o Makefile CVTrackpad.pro
/usr/share/qt/mkspecs/common/g++.conf:
/usr/share/qt/mkspecs/common/unix.conf:
/usr/share/qt/mkspecs/common/linux.conf:
/usr/share/qt/mkspecs/qconfig.pri:
/usr/share/qt/mkspecs/features/qt_functions.prf:
/usr/share/qt/mkspecs/features/qt_config.prf:
/usr/share/qt/mkspecs/features/exclusive_builds.prf:
/usr/share/qt/mkspecs/features/default_pre.prf:
/usr/share/qt/mkspecs/features/debug.prf:
/usr/share/qt/mkspecs/features/default_post.prf:
/usr/share/qt/mkspecs/features/warn_on.prf:
/usr/share/qt/mkspecs/features/qt.prf:
/usr/share/qt/mkspecs/features/unix/thread.prf:
/usr/share/qt/mkspecs/features/moc.prf:
/usr/share/qt/mkspecs/features/resources.prf:
/usr/share/qt/mkspecs/features/uic.prf:
/usr/share/qt/mkspecs/features/yacc.prf:
/usr/share/qt/mkspecs/features/lex.prf:
/usr/share/qt/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o Makefile CVTrackpad.pro

dist: 
	@$(CHK_DIR_EXISTS) src/build/CVTrackpad1.0.0 || $(MKDIR) src/build/CVTrackpad1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) src/build/CVTrackpad1.0.0/ && $(COPY_FILE) --parents MainWindow.h src/Qt/TrayIcon.h src/Qt/UIs/StartScreen.h src/ScreenRecognizer.h src/ScreenCapture.h src/Hand.h src/Gesture.h src/CaptureThread.h src/OpenCV/VideoWriter.h src/OpenCV/VideoCapture.h src/OpenCV/Tracker.h src/OpenCV/QueuedTracking.h src/OpenCV/ProcessableImage.h src/OpenCV/OpticalObject.h src/OpenCV/OpticalFlowLK.h src/OpenCV/OpticalFlow.h src/OpenCV/OpenCV.hpp src/OpenCV/OFLKTracker.h src/OpenCV/ObjectTracker.h src/OpenCV/MultipleTracker.h src/OpenCV/MeanShift.h src/OpenCV/Image.h src/OpenCV/Histogram.h src/OpenCV/HaarClassifier.h src/OpenCV/Estimator.h src/OpenCV/DrawableImage.h src/OpenCV/Capture.h src/OpenCV/CAMShift.h src/OpenCV/Camera.h src/OpenCV/BackgroundSubtraction.h src/OpenCV/include/OpenCV.h src/OpenCV/include/Macros.h src/OpenCV/include/ExternalBundle.h src/OpenCV/include/Exception.h src/Events/Mouse.h src/Qt/ImageViewWidget.h src/Qt/UIs/CameraDeviceDialog.h src/Qt/UIs/SetCornerScreen.h src/Qt/UIs/AboutScreen.h src/HandTrackerThread.h src/build/CVTrackpad1.0.0/ && $(COPY_FILE) --parents CVTrackPadResource.qrc src/build/CVTrackpad1.0.0/ && $(COPY_FILE) --parents MainWindow.cpp src/Qt/TrayIcon.cpp src/Qt/UIs/StartScreen.cpp src/ScreenRecognizer.cpp src/ScreenCapture.cpp src/Hand.cpp src/Gesture.cpp src/CaptureThread.cpp src/OpenCV/VideoWriter.cpp src/OpenCV/VideoCapture.cpp src/OpenCV/QueuedTracking.cpp src/OpenCV/ProcessableImage.cpp src/OpenCV/OpticalObject.cpp src/OpenCV/OpticalFlowLK.cpp src/OpenCV/OFLKTracker.cpp src/OpenCV/ObjectTracker.cpp src/OpenCV/MultipleTracker.cpp src/OpenCV/MeanShift.cpp src/OpenCV/Image.cpp src/OpenCV/Histogram.cpp src/OpenCV/HaarClassifier.cpp src/OpenCV/Estimator.cpp src/OpenCV/DrawableImage.cpp src/OpenCV/Capture.cpp src/OpenCV/CAMShift.cpp src/OpenCV/Camera.cpp src/OpenCV/BackgroundSubtraction.cpp main.cpp src/Events/Mouse.cpp src/Qt/ImageViewWidget.cpp src/Qt/UIs/CameraDeviceDialog.cpp src/Qt/UIs/SetCornerScreen.cpp src/Qt/UIs/AboutScreen.cpp src/HandTrackerThread.cpp src/build/CVTrackpad1.0.0/ && $(COPY_FILE) --parents MainWindow.ui src/Qt/UIs/StartScreen.ui src/Qt/UIs/CameraDeviceDialog.ui src/Qt/UIs/SetCornerScreen.ui src/Qt/UIs/AboutScreen.ui src/build/CVTrackpad1.0.0/ && (cd `dirname src/build/CVTrackpad1.0.0` && $(TAR) CVTrackpad1.0.0.tar CVTrackpad1.0.0 && $(COMPRESS) CVTrackpad1.0.0.tar) && $(MOVE) `dirname src/build/CVTrackpad1.0.0`/CVTrackpad1.0.0.tar.gz . && $(DEL_FILE) -r src/build/CVTrackpad1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_MainWindow.cpp moc_TrayIcon.cpp moc_StartScreen.cpp moc_ImageViewWidget.cpp moc_CameraDeviceDialog.cpp moc_SetCornerScreen.cpp moc_AboutScreen.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_MainWindow.cpp moc_TrayIcon.cpp moc_StartScreen.cpp moc_ImageViewWidget.cpp moc_CameraDeviceDialog.cpp moc_SetCornerScreen.cpp moc_AboutScreen.cpp
moc_MainWindow.cpp: MainWindow.h
	/usr/bin/moc $(DEFINES) $(INCPATH) MainWindow.h -o moc_MainWindow.cpp

moc_TrayIcon.cpp: src/Qt/TrayIcon.h
	/usr/bin/moc $(DEFINES) $(INCPATH) src/Qt/TrayIcon.h -o moc_TrayIcon.cpp

moc_StartScreen.cpp: src/Qt/UIs/StartScreen.h
	/usr/bin/moc $(DEFINES) $(INCPATH) src/Qt/UIs/StartScreen.h -o moc_StartScreen.cpp

moc_ImageViewWidget.cpp: src/Qt/ImageViewWidget.h
	/usr/bin/moc $(DEFINES) $(INCPATH) src/Qt/ImageViewWidget.h -o moc_ImageViewWidget.cpp

moc_CameraDeviceDialog.cpp: src/Qt/UIs/CameraDeviceDialog.h
	/usr/bin/moc $(DEFINES) $(INCPATH) src/Qt/UIs/CameraDeviceDialog.h -o moc_CameraDeviceDialog.cpp

moc_SetCornerScreen.cpp: src/Qt/UIs/SetCornerScreen.h
	/usr/bin/moc $(DEFINES) $(INCPATH) src/Qt/UIs/SetCornerScreen.h -o moc_SetCornerScreen.cpp

moc_AboutScreen.cpp: src/Qt/UIs/AboutScreen.h
	/usr/bin/moc $(DEFINES) $(INCPATH) src/Qt/UIs/AboutScreen.h -o moc_AboutScreen.cpp

compiler_rcc_make_all: qrc_CVTrackPadResource.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_CVTrackPadResource.cpp
qrc_CVTrackPadResource.cpp: CVTrackPadResource.qrc \
		images/universidad.jpg \
		images/bad.svg \
		images/webcam.ico \
		images/exewebcam.ico \
		images/universidad_de_deusto.jpg
	/usr/bin/rcc -name CVTrackPadResource CVTrackPadResource.qrc -o qrc_CVTrackPadResource.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_MainWindow.h ui_StartScreen.h ui_CameraDeviceDialog.h ui_SetCornerScreen.h ui_AboutScreen.h
compiler_uic_clean:
	-$(DEL_FILE) ui_MainWindow.h ui_StartScreen.h ui_CameraDeviceDialog.h ui_SetCornerScreen.h ui_AboutScreen.h
ui_MainWindow.h: MainWindow.ui
	/usr/bin/uic MainWindow.ui -o ui_MainWindow.h

ui_StartScreen.h: src/Qt/UIs/StartScreen.ui
	/usr/bin/uic src/Qt/UIs/StartScreen.ui -o ui_StartScreen.h

ui_CameraDeviceDialog.h: src/Qt/UIs/CameraDeviceDialog.ui
	/usr/bin/uic src/Qt/UIs/CameraDeviceDialog.ui -o ui_CameraDeviceDialog.h

ui_SetCornerScreen.h: src/Qt/UIs/SetCornerScreen.ui
	/usr/bin/uic src/Qt/UIs/SetCornerScreen.ui -o ui_SetCornerScreen.h

ui_AboutScreen.h: src/Qt/UIs/AboutScreen.ui
	/usr/bin/uic src/Qt/UIs/AboutScreen.ui -o ui_AboutScreen.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

src/build/MainWindow.o: MainWindow.cpp MainWindow.h \
		ui_MainWindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/MainWindow.o MainWindow.cpp

src/build/TrayIcon.o: src/Qt/TrayIcon.cpp src/Qt/TrayIcon.h \
		MainWindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/TrayIcon.o src/Qt/TrayIcon.cpp

src/build/StartScreen.o: src/Qt/UIs/StartScreen.cpp src/Qt/UIs/StartScreen.h \
		ui_StartScreen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/StartScreen.o src/Qt/UIs/StartScreen.cpp

src/build/ScreenRecognizer.o: src/ScreenRecognizer.cpp src/ScreenRecognizer.h \
		src/OpenCV/Capture.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h \
		src/OpenCV/ProcessableImage.h \
		src/OpenCV/DrawableImage.h \
		src/OpenCV/OpticalObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/ScreenRecognizer.o src/ScreenRecognizer.cpp

src/build/ScreenCapture.o: src/ScreenCapture.cpp src/ScreenCapture.h \
		src/OpenCV/Capture.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h \
		src/ScreenRecognizer.h \
		src/OpenCV/ProcessableImage.h \
		src/OpenCV/DrawableImage.h \
		src/OpenCV/OpticalObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/ScreenCapture.o src/ScreenCapture.cpp

src/build/Hand.o: src/Hand.cpp src/Hand.h \
		src/OpenCV/Histogram.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/DrawableImage.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h \
		src/OpenCV/OpticalObject.h \
		src/OpenCV/ProcessableImage.h \
		src/OpenCV/HaarClassifier.h \
		src/OpenCV/CAMShift.h \
		src/OpenCV/MeanShift.h \
		src/OpenCV/Tracker.h \
		src/OpenCV/OFLKTracker.h \
		src/OpenCV/include/Macros.h \
		src/OpenCV/OpticalFlowLK.h \
		src/OpenCV/OpticalFlow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/Hand.o src/Hand.cpp

src/build/Gesture.o: src/Gesture.cpp src/Gesture.h \
		src/Hand.h \
		src/OpenCV/Histogram.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/DrawableImage.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h \
		src/OpenCV/OpticalObject.h \
		src/OpenCV/ProcessableImage.h \
		src/OpenCV/HaarClassifier.h \
		src/OpenCV/CAMShift.h \
		src/OpenCV/MeanShift.h \
		src/OpenCV/Tracker.h \
		src/OpenCV/OFLKTracker.h \
		src/OpenCV/include/Macros.h \
		src/OpenCV/OpticalFlowLK.h \
		src/OpenCV/OpticalFlow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/Gesture.o src/Gesture.cpp

src/build/CaptureThread.o: src/CaptureThread.cpp src/CaptureThread.h \
		src/OpenCV/Capture.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/CaptureThread.o src/CaptureThread.cpp

src/build/VideoWriter.o: src/OpenCV/VideoWriter.cpp src/OpenCV/VideoWriter.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/VideoWriter.o src/OpenCV/VideoWriter.cpp

src/build/VideoCapture.o: src/OpenCV/VideoCapture.cpp src/OpenCV/VideoCapture.h \
		src/OpenCV/include/Exception.h \
		src/OpenCV/Capture.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/Image.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/VideoCapture.o src/OpenCV/VideoCapture.cpp

src/build/QueuedTracking.o: src/OpenCV/QueuedTracking.cpp src/OpenCV/QueuedTracking.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/include/Exception.h \
		src/OpenCV/Tracker.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/QueuedTracking.o src/OpenCV/QueuedTracking.cpp

src/build/ProcessableImage.o: src/OpenCV/ProcessableImage.cpp src/OpenCV/ProcessableImage.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/ProcessableImage.o src/OpenCV/ProcessableImage.cpp

src/build/OpticalObject.o: src/OpenCV/OpticalObject.cpp src/OpenCV/OpticalObject.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/ProcessableImage.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h \
		src/OpenCV/DrawableImage.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/OpticalObject.o src/OpenCV/OpticalObject.cpp

src/build/OpticalFlowLK.o: src/OpenCV/OpticalFlowLK.cpp src/OpenCV/OpticalFlowLK.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/OpticalFlow.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/OpticalFlowLK.o src/OpenCV/OpticalFlowLK.cpp

src/build/OFLKTracker.o: src/OpenCV/OFLKTracker.cpp src/OpenCV/OFLKTracker.h \
		src/OpenCV/include/Macros.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/Tracker.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h \
		src/OpenCV/DrawableImage.h \
		src/OpenCV/OpticalObject.h \
		src/OpenCV/ProcessableImage.h \
		src/OpenCV/OpticalFlowLK.h \
		src/OpenCV/OpticalFlow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/OFLKTracker.o src/OpenCV/OFLKTracker.cpp

src/build/ObjectTracker.o: src/OpenCV/ObjectTracker.cpp src/OpenCV/ObjectTracker.h \
		src/OpenCV/include/Macros.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/OpticalObject.h \
		src/OpenCV/ProcessableImage.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h \
		src/OpenCV/MeanShift.h \
		src/OpenCV/Histogram.h \
		src/OpenCV/DrawableImage.h \
		src/OpenCV/Tracker.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/ObjectTracker.o src/OpenCV/ObjectTracker.cpp

src/build/MultipleTracker.o: src/OpenCV/MultipleTracker.cpp src/OpenCV/MultipleTracker.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/Tracker.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/MultipleTracker.o src/OpenCV/MultipleTracker.cpp

src/build/MeanShift.o: src/OpenCV/MeanShift.cpp src/OpenCV/MeanShift.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/Histogram.h \
		src/OpenCV/DrawableImage.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h \
		src/OpenCV/OpticalObject.h \
		src/OpenCV/ProcessableImage.h \
		src/OpenCV/Tracker.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/MeanShift.o src/OpenCV/MeanShift.cpp

src/build/Image.o: src/OpenCV/Image.cpp src/OpenCV/Image.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/include/Exception.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/Image.o src/OpenCV/Image.cpp

src/build/Histogram.o: src/OpenCV/Histogram.cpp src/OpenCV/Histogram.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/DrawableImage.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h \
		src/OpenCV/OpticalObject.h \
		src/OpenCV/ProcessableImage.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/Histogram.o src/OpenCV/Histogram.cpp

src/build/HaarClassifier.o: src/OpenCV/HaarClassifier.cpp src/OpenCV/HaarClassifier.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/include/Exception.h \
		src/OpenCV/Image.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/HaarClassifier.o src/OpenCV/HaarClassifier.cpp

src/build/Estimator.o: src/OpenCV/Estimator.cpp src/OpenCV/Estimator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/Estimator.o src/OpenCV/Estimator.cpp

src/build/DrawableImage.o: src/OpenCV/DrawableImage.cpp src/OpenCV/DrawableImage.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h \
		src/OpenCV/OpticalObject.h \
		src/OpenCV/ProcessableImage.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/DrawableImage.o src/OpenCV/DrawableImage.cpp

src/build/Capture.o: src/OpenCV/Capture.cpp src/OpenCV/Capture.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/Capture.o src/OpenCV/Capture.cpp

src/build/CAMShift.o: src/OpenCV/CAMShift.cpp src/OpenCV/CAMShift.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/MeanShift.h \
		src/OpenCV/Histogram.h \
		src/OpenCV/DrawableImage.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h \
		src/OpenCV/OpticalObject.h \
		src/OpenCV/ProcessableImage.h \
		src/OpenCV/Tracker.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/CAMShift.o src/OpenCV/CAMShift.cpp

src/build/Camera.o: src/OpenCV/Camera.cpp src/OpenCV/Camera.h \
		src/OpenCV/include/Exception.h \
		src/OpenCV/Capture.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/Image.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/Camera.o src/OpenCV/Camera.cpp

src/build/BackgroundSubtraction.o: src/OpenCV/BackgroundSubtraction.cpp src/OpenCV/BackgroundSubtraction.h \
		src/OpenCV/include/Macros.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/include/Exception.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/BackgroundSubtraction.o src/OpenCV/BackgroundSubtraction.cpp

src/build/main.o: main.cpp MainWindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/main.o main.cpp

src/build/Mouse.o: src/Events/Mouse.cpp src/Events/Mouse.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/Mouse.o src/Events/Mouse.cpp

src/build/ImageViewWidget.o: src/Qt/ImageViewWidget.cpp src/Qt/ImageViewWidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/ImageViewWidget.o src/Qt/ImageViewWidget.cpp

src/build/CameraDeviceDialog.o: src/Qt/UIs/CameraDeviceDialog.cpp src/Qt/UIs/CameraDeviceDialog.h \
		ui_CameraDeviceDialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/CameraDeviceDialog.o src/Qt/UIs/CameraDeviceDialog.cpp

src/build/SetCornerScreen.o: src/Qt/UIs/SetCornerScreen.cpp src/Qt/UIs/SetCornerScreen.h \
		ui_SetCornerScreen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/SetCornerScreen.o src/Qt/UIs/SetCornerScreen.cpp

src/build/AboutScreen.o: src/Qt/UIs/AboutScreen.cpp src/Qt/UIs/AboutScreen.h \
		ui_AboutScreen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/AboutScreen.o src/Qt/UIs/AboutScreen.cpp

src/build/HandTrackerThread.o: src/HandTrackerThread.cpp src/HandTrackerThread.h \
		src/OpenCV/OpenCV.hpp \
		src/OpenCV/DrawableImage.h \
		src/OpenCV/include/OpenCV.h \
		src/OpenCV/Image.h \
		src/OpenCV/include/Exception.h \
		src/OpenCV/OpticalObject.h \
		src/OpenCV/ProcessableImage.h \
		src/OpenCV/BackgroundSubtraction.h \
		src/OpenCV/include/Macros.h \
		src/OpenCV/Camera.h \
		src/OpenCV/Capture.h \
		src/OpenCV/VideoCapture.h \
		src/OpenCV/VideoWriter.h \
		src/OpenCV/HaarClassifier.h \
		src/OpenCV/CAMShift.h \
		src/OpenCV/MeanShift.h \
		src/OpenCV/Histogram.h \
		src/OpenCV/Tracker.h \
		src/OpenCV/OFLKTracker.h \
		src/OpenCV/OpticalFlowLK.h \
		src/OpenCV/OpticalFlow.h \
		src/OpenCV/ObjectTracker.h \
		src/OpenCV/MultipleTracker.h \
		src/Hand.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/HandTrackerThread.o src/HandTrackerThread.cpp

src/build/moc_MainWindow.o: moc_MainWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/moc_MainWindow.o moc_MainWindow.cpp

src/build/moc_TrayIcon.o: moc_TrayIcon.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/moc_TrayIcon.o moc_TrayIcon.cpp

src/build/moc_StartScreen.o: moc_StartScreen.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/moc_StartScreen.o moc_StartScreen.cpp

src/build/moc_ImageViewWidget.o: moc_ImageViewWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/moc_ImageViewWidget.o moc_ImageViewWidget.cpp

src/build/moc_CameraDeviceDialog.o: moc_CameraDeviceDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/moc_CameraDeviceDialog.o moc_CameraDeviceDialog.cpp

src/build/moc_SetCornerScreen.o: moc_SetCornerScreen.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/moc_SetCornerScreen.o moc_SetCornerScreen.cpp

src/build/moc_AboutScreen.o: moc_AboutScreen.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/moc_AboutScreen.o moc_AboutScreen.cpp

src/build/qrc_CVTrackPadResource.o: qrc_CVTrackPadResource.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o src/build/qrc_CVTrackPadResource.o qrc_CVTrackPadResource.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

