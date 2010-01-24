/*
 */

#if 0
#include "OpenCV/OpenCV.hpp"

#include "Hand.h"
#include "CaptureThread.h"
#include <stdio.h>
#include "time.h"

#include <QtCore/QThread>

#include "config.h"

#include <iostream>

using namespace OpenCV;
using namespace OpenCV::Tracking;
using namespace OpenCV::VideoIO;
using namespace OpenCV::VectorizedGraphics;
using namespace HumanInterface;

const char* CASCADE_NAME = "C:/Documents and Settings/Administrador/Escritorio/endika/data/haarcascades/haarcascade_frontalface_default.xml";

/**
 *  \warning NOT SAFE THREAD!!! USE MUTEX!!!
 */
class TrackerThread : public QThread {
public:
    TrackerThread(Tracker*& tracker, Image*& image)
        : QThread()
    {
        m_tracker = &tracker;
        m_image = &image;
    }

    /**
     *  Gets last tracked ConnectedComponents
     *  \warning You migth need mutex here
     *  \return Last tracked CvConnectedComponents
     */
    inline CvConnectedComp* trackedComponent() { return m_trackedComponents; }
    
protected:
    virtual void run() 
    {
#ifdef DEBUG
        double time = clock();
        unsigned int count = 0;
#endif // DEBUG

        forever {
            if (!m_image || !(*m_image))
                continue;

            // Better if we copied this
            Image* trackingImage = (*m_image)->clone();

            if (*m_tracker) {
                cvReleaseConnectedComp(m_trackedComponents);
                m_trackedComponents = (*m_tracker)->track(trackingImage);
#ifdef DEBUG
                static char* s = new char[64];  // Buffer for outbput debug
                sprintf(s, "; fps = %2.2f; Area = %.2f; count = %u",
                        CLOCKS_PER_SEC / (clock()-time),
                        (m_trackedComponents->area / 10000),
                        ++count);
                time = clock();
                std::cout << m_trackedComponents->rect.x + m_trackedComponents->rect.width / 2 << ", "
                          << m_trackedComponents->rect.y + m_trackedComponents->rect.height / 2
                          << s << "\n";
#endif // DEBUG
            }

            delete trackingImage;
        }
    }

protected:
    Tracker** m_tracker;
    Image** m_image;
    CvConnectedComp* m_trackedComponents;
};


//#define LEARN_COLOR

#ifndef LEARN_COLOR
using namespace OpenCV::MachineLearning;
#endif

int main(int argc, char** args)
{
    Camera* p_camera;
    Image* image;

    try {
        p_camera = new Camera(DEFAULT_CAMERA);
    } catch (DeviceNotFoundException& ex) {
        delete p_camera;
        std::cerr << ex;
        exit(0x10);
    }


#ifndef LEARN_COLOR
    HaarClassifier* faceClassifier;
    try {
        faceClassifier = new HaarClassifier(CASCADE_NAME);
    } catch (FileNotFoundException& ex) {
        delete p_camera;
        delete faceClassifier;
        std::cerr << ex;
        exit(0x11);
    }
#endif

    CaptureThread captureThread(*p_camera, image, 20.0);

    CodeBookSubstraction cbs;
    Hand* hand = NULL;

    captureThread.startCapturing();

#ifdef LEARN_COLOR
    for (int i = 60; i--; /*image = */ camera.captureFrame()) {
        cbs.learnBackground(image);
        DrawableImage* dImage = static_cast<DrawableImage*> (image->clone());
        dImage->drawRectangle(cvRect(500, 340, 60, 60), 3, COLOR_RED);
        dImage->showImage("hand");
        delete dImage;
    }
    DrawableImage* mask = new DrawableImage(image->size(), UByte, 1);
    mask->drawBox(cvRect(500, 340, 60, 60), COLOR_WHITE);
    Histogram* handHistogram = Histogram::createHSHistogram(image, mask);
    delete mask;
#else
    for (int i = 60; i--; )
        cbs.learnBackground(image);
#endif
    
    image->showImage("hand");

    Tracker* handTracker = NULL;
    
    TrackerThread tracking(handTracker, image);
    tracking.start();

    char* s = new char[32];
    double time = clock();
    unsigned long count = 0;
    

    for (; ; ) {
        DrawableImage* dImage = static_cast<DrawableImage*> (image->clone());
        Mask* backgroundSubsMask = cbs.subtractBackground(dImage);
#ifdef LEARN_COLOR
        if (hand = Hand::handFromHistogram(handHistogram, image, backgroundSubsMask)) {
#else
        if (hand = Hand::handFromFaceCascade(faceClassifier, dImage, backgroundSubsMask)) {
#endif
            handTracker = hand->handTracker(dImage);

            delete hand;
            dImage->drawContour(hand->opticalObject(), COLOR_GREEN, 3);
#if 0
            DrawableImage* mask = new DrawableImage(image->size(), UByte, 1);
            mask->drawObject(hand->opticalObject(), COLOR_WHITE);

            delete mask;
            Histogram* newHistogram = Histogram::createHSHistogram(image, mask);
            printf("%f\n", newHistogram->calcEMD2(handHistogram, EuclideanDistance));
            delete handHistogram;
            handHistogram = newHistogram;
#endif
        }
        sprintf(s, "fps = %2.2f; count = %u\0", CLOCKS_PER_SEC / (clock()-time), ++count);
        time = clock();
        dImage->drawText(s, cvPoint(4,28), .6l, COLOR_WHITE);
        dImage->showImage("hand");

        delete backgroundSubsMask;
        delete dImage;
    }
    
    assert(0);
    
    return -1; //Should never end
}
#endif
