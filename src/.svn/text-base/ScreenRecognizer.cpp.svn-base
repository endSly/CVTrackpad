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


#include "ScreenRecognizer.h"

namespace HumanInterface {
	
const int defaultRows = 5;
const int defaultColumns = 8;

ScreenRecognizer::ScreenRecognizer(Capture* cam)
	: m_camera(cam)
	, m_corners(NULL)
	, m_didRecognize(false)
{
}
	
	
ScreenRecognizer::~ScreenRecognizer()
{
	if (m_corners)	
		delete m_corners;
	delete m_camera;
}

void ScreenRecognizer::recognize()
{
	if (!m_camera)
		return;
		
	//create chessboard image and show at full screen
	Image* chessboardImage = createChessboardImage(cvSize(1280, 800), defaultRows, defaultColumns);
	chessboardImage->showImage("Cheesboard");
	
	for(Image* image = (Image*)m_camera->captureFrame()
		; newFrameForRecognize(image)
		; m_camera->captureFrame()) { }

}
	
Image* ScreenRecognizer::createChessboardImage(CvSize size, int rows, int columns)
{
	DrawableImage* chessboard = new DrawableImage(size, IPL_DEPTH_8U, 1);	//Grey image
	
	CvPoint pt1, pt2;
	CvScalar blackWhite[2] = { cvScalar(0), cvScalar(255)};
	
	for (int x = 0; x < columns; x++) 
		for (int y = 0; y < rows; y++) {
			pt1.x = x * size.width / columns;
			pt1.y = y * size.height / rows;
			pt2.x = (x + 1) * size.width / columns;
			pt2.y = (y + 1) * size.height / rows;
			chessboard->drawBox(pt1, pt2, blackWhite[(x + y) % 2]);
		}
	return (Image*) chessboard; 
}

	
CvPoint2D32f* ScreenRecognizer::findCornerPoints(const CvPoint2D32f* points, int columns, int rows)
{
	const int topLeft = 0;
	const int topRigth = 1;
	const int bottomLeft = 2;
	const int bottomRigth = 3;

	CvPoint2D32f* m = new CvPoint2D32f[4];
	m[0] = m[1] = m[2] = m[3] = points[0];
	
	//Find 4 corner points
	for (int i = 0; i < columns * rows; i++) {
		/* Top left */
		if ((points[i].x + points[i].y) < (m[topLeft].x + m[topLeft].y))
			m[topLeft] = points[i];
		/* Bottom rigth */
		else if ((points[i].x + points[i].y) > (m[bottomRigth].x + m[bottomRigth].y))
			m[bottomRigth] = points[i];
		/* Top rigth */
		if ((points[i].x / points[i].y) > (m[topRigth].x / m[topRigth].y))
			m[topRigth] = points[i];
		/* Bottom left */
		else if ((points[i].x / points[i].y) < (m[bottomLeft].x / m[bottomLeft].y))
			m[bottomLeft] = points[i];
	}
	return m;
}

void ScreenRecognizer::correctProportionalCornersOfScreen(CvPoint2D32f* points, int columns, int rows)
{
	const int topLeft = 0;
	const int topRigth = 1;
	const int bottomLeft = 2;
	const int bottomRigth = 3;
	
	//This corners are not yet corners of screen, border squares of chessboard are not detected
	//Add size of square
	points[topLeft].x -= (points[topRigth].x - points[topLeft].x) / columns;
	points[topLeft].y -= (points[bottomLeft].y - points[topLeft].y) / rows;
	
	points[topRigth].x += (points[topRigth].x - points[topLeft].x) / columns;
	points[topRigth].y -= (points[bottomRigth].y - points[topRigth].y) / rows;
	
	points[bottomLeft].x -= (points[bottomRigth].x - points[bottomLeft].x) / columns;
	points[bottomLeft].y += (points[bottomLeft].y - points[topLeft].y) / rows;
	
	points[bottomRigth].x += (points[bottomRigth].x - points[bottomLeft].x) / columns;
	points[bottomRigth].y += (points[bottomRigth].y - points[topRigth].y) / rows;
}

bool ScreenRecognizer::newFrameForRecognize(Image* frame)
{
	ProcessableImage* pimage = new ProcessableImage((ProcessableImage)*frame);
	CvPoint2D32f* pts = pimage->findChessboardCorners(defaultColumns, defaultRows);
	
	for (int i = 0; i < (defaultColumns * defaultRows); i++) {
		if ((pts[i].x == 0.0f) && (pts[i].y == 0.0f))
			return false;		//Not recognized all points yet
		pts[i].y = pimage->size().height - pts[i].y;	//findChessboarCorners works with y-swaped image
	} //All points found

	
	//static functions forbids acces o members
	m_corners = findCornerPoints(pts, defaultColumns, defaultRows);		//Locate corners
	//This corners are not yet corners of screen, border squares of chessboard are not detected
	correctProportionalCornersOfScreen(m_corners, defaultColumns, defaultRows);
	
#ifdef DEBUG
	printf("Screen Recognized.\n");
	
#ifdef WEBCAM_DEBUG
	DrawableImage* image = (DrawableImage*)frame;
	
	for(int i = 0; i < 18; i++)
		image->drawLine(cvPoint(pts[i].x, pts[i].y), cvPoint(pts[i].x, pts[i].y), 4 , cvScalar(0,0,255));
	
	image->drawLine(cvPoint(m_corners[0].x, m_corners[0].y), cvPoint(m_corners[1].x, m_corners[1].y), 2 , cvScalar(0,255,0));
	image->drawLine(cvPoint(m_corners[1].x, m_corners[1].y), cvPoint(m_corners[3].x, m_corners[3].y), 2 , cvScalar(0,255,0));
	image->drawLine(cvPoint(m_corners[2].x, m_corners[2].y), cvPoint(m_corners[3].x, m_corners[3].y), 2 , cvScalar(0,255,0));
	image->drawLine(cvPoint(m_corners[2].x, m_corners[2].y), cvPoint(m_corners[0].x, m_corners[0].y), 2 , cvScalar(0,255,0));
	
	frame->showImage("win");
	
	Image* wimage = pimage->warpPerspective(m_corners);
	
	wimage->showImage("warp");
	
#endif //WEBCAM_DEBUG
	
#endif //DEBUG
	
	m_didRecognize = true;
	
	return true;
}
	
} // namespace HumanInterface
