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


#include "OpticalObject.h"
#include "DrawableImage.h"  /* DrawableImage imports OpticalObject.h */

inline double CV_RECT_AREA(const CvRect& r) { return (r.width * r.height); }
inline bool CV_RECT_EQUAL(const CvRect& r0, const CvRect& r1) { return ((r0.x == r1.x) && (r0.y == r1.y) && (r0.width == r1.width) && (r0.height == r1.height)); };

namespace OpenCV {
    
namespace VectorizedGraphics {
    
OpticalObject::OpticalObject()
    : m_objectComponents(new CvConnectedComp)
{
}

OpticalObject::OpticalObject(CvConnectedComp* comp)
    : m_objectComponents(comp)
{
}

OpticalObject::OpticalObject(const OpticalObject& optObj)
    : m_objectComponents(optObj.m_objectComponents)
{
}

OpticalObject::~OpticalObject()
{
    if (m_objectComponents
        && m_objectComponents->contour
        && m_objectComponents->contour->storage) { }
    //cvReleaseMemStorage(&(m_objectComponents->contour->storage)); // Release Storage

    //delete m_objectComponents; // Release struct
}

double OpticalObject::area() const
{
    if (!m_objectComponents)
        return 0.0;
    // By default does not calculate object's area, only if request
    if (!m_objectComponents->area)
        m_objectComponents->area = fabs(cvContourArea(m_objectComponents->contour, CV_WHOLE_SEQ));
    
    return m_objectComponents->area;
}

CvRect OpticalObject::rect() const
{
    if (!m_objectComponents)
        return CV_RECT_ZERO;
    // By default does not calculate object's rect, only if request
    if (CV_RECT_EQUAL(m_objectComponents->rect, CV_RECT_ZERO))
        m_objectComponents->rect = cvContourBoundingRect(m_objectComponents->contour, true);
    
    return m_objectComponents->rect;
}

OpticalObjects* OpticalObject::opticalObjectsFromImage(const Image* image, double minPerimeter, int method)
{
    Image* grayImage = image->numberOfChannels() > 1 ? Image::convert(image, CV_BGR2GRAY) : image->clone(); //We need 1ch image
    CvSeq* contours = polygonalContours(grayImage, method, minPerimeter);
    delete grayImage;
    OpticalObjects* objects = new OpticalObjects;
    
    for (CvSeq* seq = contours; seq; seq = seq->h_next) {
        CvConnectedComp* cComp = new CvConnectedComp;
        cComp->contour = seq;
        cComp->area = 0;
        cComp->rect = CV_RECT_ZERO;
        objects->insert(objects->end(), new OpticalObject(cComp));
    }
    // Do not delete seq here, will be deleted with destructor
    return objects;
}

Mask* OpticalObject::maskFromUnconnectedMask(const Mask* mask, double minPerimeter)
{
    Image* grayMask = mask->numberOfChannels() > 1 ? Image::convert(mask, CV_BGR2GRAY) : mask->clone(); //We need 1ch image
    CvSeq* contours = polygonalContours(grayMask, ChainApproxSimple, minPerimeter);
    Mask* connectedMask = new Image(mask->size(), UByte, 1);
    
    for (CvSeq* seq = contours; seq; seq = seq->h_next) 
        cvDrawContours(connectedMask->cvImage(),
                       seq, 
                       cvScalar(255),
                       cvScalar(255),
                       -1,
                       CV_FILLED,
                       8);
    if (contours && contours->storage)
        cvClearMemStorage(contours->storage);
    cvRelease((void**)&contours);
    delete grayMask;
    
    return connectedMask;
}

OpticalObject* OpticalObject::convexHull(int orientation, int pointsCount)
{
    CvSeq* convexContour = cvConvexHull2(m_objectComponents->contour, 
                                         NULL, 
                                         orientation, 
                                         pointsCount);
    CvConnectedComp* convexComponents = new CvConnectedComp;
    convexComponents->contour = convexContour;
    return new OpticalObject(convexComponents);
}
        
OpticalObjects* OpticalObject::convexityDefects(OpticalObject*, OpticalObject*)
{
    throw "NotImplementedException";
}
    
bool OpticalObject::isOnRect(const CvRect& superRect)
{
    CvRect sharedRect = cvRect(superRect.x > rect().x ? superRect.x : rect().x,  //Max X and Y
                               superRect.y > rect().y ? superRect.y : rect().y, 
                               0,   //Unknown Width and height
                               0);
    // Calculate common area
    sharedRect.width = (superRect.x + superRect.width) < (rect().x + rect().width) 
                        ? (superRect.x + superRect.width) - sharedRect.x 
                        : (rect().x + rect().width) - sharedRect.x;
    
    sharedRect.height = (superRect.y + superRect.height) < (rect().y + rect().height) 
                        ? (superRect.y + superRect.height) - sharedRect.y 
                        : (rect().y + rect().height) - sharedRect.y;
    
    return ((2 * CV_RECT_AREA(sharedRect)) >= CV_RECT_AREA(rect()))     /* minimum half of area */
        || ((2 * CV_RECT_AREA(sharedRect)) >= CV_RECT_AREA(superRect));
    
}
    
CvSeq* OpticalObject::polygonalContours(Image* image, 
                                        int method, 
                                        double minPerimeter)
{
    // internal function, may be asserted
    assert(image->numberOfChannels() == 1);
    /*  Not very good idea to make mem storage static because
     *  two diferent process can create OpticalObjects and
     *  it's memory can't be shared.
     *  But!!! If not static may be imposible to release because
     *  all optical objects share the same memStorage and it has to be
     *  released when every object has been released.
     */
#if 1
    static
#endif
    CvMemStorage* memStorage = NULL;


    //Create mem storage or reuse old
#if 1
    if (memStorage)
        cvClearMemStorage(memStorage);
    else
#endif
        memStorage = cvCreateMemStorage(0);
    
#ifdef DEFAULT_MASK_THRESHOLD
    //pImage->threshold(DEFAULT_MASK_THRESHOLD, 255, Binary);
#endif // DEFAULT_MASK_THRESHOLD
    
    //Clear image
    //pImage->morphologyEx(Open, 1); 
    //pImage->morphologyEx(Close, 1);
    
    CvContourScanner scanner = cvStartFindContours(image->cvImage(),
                                                   memStorage, 
                                                   sizeof(CvContour), 
                                                   CV_RETR_EXTERNAL, 
                                                   method);

    for (CvSeq* currentContourSeq = cvFindNextContour(scanner);
         currentContourSeq;
         currentContourSeq = cvFindNextContour(scanner)) {
        cvSubstituteContour(scanner,        //Substitute contour 
                            ((cvContourPerimeter(currentContourSeq) >= minPerimeter)
                             ? cvApproxPoly(currentContourSeq,   //With Poligonal Contour
                                            sizeof(CvContour),
                                            memStorage, 
                                            DEFAULT_POLYGONAL_APPROX_ALG,
                                            2, //Approximation level
                                            0) //Not used
                             : NULL));    //else delete contour
    }
    return cvEndFindContours(&scanner);
}
    

    
Mask* OpticalObject::toMask() const
{
    DrawableImage* mask = new DrawableImage(cvSize(640, 480), UByte, 1);
    mask->drawObject(this, cvScalar(255));
    return mask;
}
    
} // namespace VectorizedGraphics
    
} // namespace OpenCV

