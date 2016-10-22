#ifndef TDBK_COMMON
#define TDBK_COMMON

#include "common.h"
#include <cmath>

// Global variables are described in header file
unsigned int winWidth = 500;
unsigned int winHeight = 500;

double xComplexMin = -2.00, xComplexMax = .50;
double yComplexMin = -1.25, yComplexMax = 1.25;

double complexWidth = xComplexMax - xComplexMin;
double complexHeight = yComplexMax - yComplexMin;

const double ZOOM_FACTOR = .1;
const int PIXEL_PAN  = 10;

Complex mouseCoords;
bool isMouseClicked = false;
int screenMouseX = 0;
int screenMouseY = 0;

bool isMandelbrotSet = true;
bool isParallel = true;
bool isAnimating = false;

/*
Name: plotPoint
Author: Code from the book modified by Benjamin Kaiser and Taylor Doell
Description: This function takes a single point in the structure format and the
different components then get passed to the glVertex2d command to be printed on
the screen.
*/
void plotPoint(Complex z)
{
	glVertex2d(z.x, z.y);
}

/*
Name: complexSquareSerial
Author: Code from the book modified by Benjamin Kaiser and Taylor Doell
Description: This function takes a single point in the complex structure format
and then computes the complex number multiplication operations to square the number
*/
Complex complexSquareSerial(Complex z)
{
	Complex zSquare;

	zSquare.x = (z.x * z.x) - (z.y * z.y);
	zSquare.y = 2 * z.x * z.y;

	return zSquare;
}

/*
Name: SetColorAndPlot
Author: Benjamin Kaiser and Taylor Doell
Description:  This function takes the divergence limit (maxIter), the interations
that the point was computed on, the point itself, and then a vector which describes
a specific color palette.  There is then a large if-else statement which
compares the actual number of iterations computed on the point to a range of the
max iterations and assigns the correct color accordingly.  The color value associated
with this specific point is then set and the current color utilized by OpenGL is
set with that color.  The point is then passed to the plotPoint function which handles
printing it on the screen.
*/
void SetColorAndPlot(int maxIter, int interations, Complex zPoint, vector<Color> colorSet)
{
    Color ptColor(0, 0, 0);

    // Choose correct color based off of iterations being compared to maxIter
	if (interations >= maxIter)
	{
        ptColor = colorSet[0];
	}
	else if (interations > (maxIter / 8))
	{
        ptColor = colorSet[1];
	}
	else if (interations > (maxIter / 10))
	{
        ptColor = colorSet[2];
	}
	else if (interations > (maxIter/20))
	{
        ptColor = colorSet[3];
	}
	else if (interations > (maxIter/40))
	{
        ptColor = colorSet[4];
	}
	else if (interations > (maxIter/100))
	{
        ptColor = colorSet[5];
	}
	else
	{
        ptColor = colorSet[6];
	}

    // Set current color and plot the point
	glColor3ub(ptColor.red, ptColor.green, ptColor.blue);
	plotPoint(zPoint);
}

/*
name: zoom
Author: Benjamin Kaiser and Taylor Doell
Description:  This function is the function which handles the setting of all of the
values associated with zooming.  It takes a percentage which is the percentage of
the overall width/height taken off one side of the corresponding values (e.g. 10%
of the overall width is taken off of each side of the width.  This makes it a 20%
cut in total).  The new min and maxes are computed using this percentages and
are added to or subtracted from respectively to get the new values.
The distance of our current mouse coordinates from the coordinates that make
up the center of the screen are computed and when we zoom in or out, the coordinates
that our mouse was pointing at when the button was fired, move to the
center of the screen and everything else moves with it.
*/
void zoom(double percentage)
{
		double xOffset, yOffset;

		// zoom x
		xComplexMin = xComplexMin + (complexWidth) * percentage;
		xComplexMax = xComplexMax - (complexWidth) * percentage;

		complexWidth = xComplexMax - xComplexMin;

		xOffset = mouseCoords.x - (xComplexMax - (complexWidth / 2.0));

		xComplexMin = xComplexMin + xOffset;
		xComplexMax = xComplexMax + xOffset;

		// zoom y
		yComplexMin = yComplexMin + (complexHeight) * percentage;
		yComplexMax = yComplexMax - (complexHeight) * percentage;

		complexHeight = yComplexMax - yComplexMin;

		yOffset = mouseCoords.y - (yComplexMax - (complexHeight / 2.0));

		yComplexMin = yComplexMin + yOffset;
		yComplexMax = yComplexMax + yOffset;

		glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();

		gluOrtho2D(xComplexMin, xComplexMax, yComplexMin, yComplexMax);
}

/*
Name: pan
Author: Benjamin Kaiser and Taylor Doell
Description:  This function handles the panning functionality for the screen.
The function takes two offset values in pixels which are telling it how far to move
in the left/right and up/down directions.  The cartesian coordinates of the center
of the screen plus these offset values are computer and the
x and y offsets are then computed and added to the complex min and maxes to slide
the screen in the specific direction.
*/
void pan(int xPixOffset, int yPixOffset)
{

	double xOffset, yOffset;
	double xCenterPixel = winWidth / 2.0;
	double yCenterPixel = winHeight / 2.0;

	mouseCoords = getViewCoordinates(xCenterPixel + xPixOffset, yCenterPixel + yPixOffset);

	xOffset = mouseCoords.x - (xComplexMax - (complexWidth / 2.0));

	yOffset = mouseCoords.y - (yComplexMax - (complexHeight / 2.0));

	xComplexMax = xComplexMax + xOffset;
	xComplexMin = xComplexMin + xOffset;

	yComplexMax = yComplexMax + yOffset;
	yComplexMin = yComplexMin + yOffset;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(xComplexMin, xComplexMax, yComplexMin, yComplexMax);
}

/*
Name: getViewCoordinates
Author: Benjamin Kaiser and Taylor Doell
Description:  This function takes two values which are pixel coordinates on the
device and converts them into cartesian coordinates in  the world scene.  This
is done by calculating the width and height of the display in cartesian values.
Since we assume that the thing will be square we use the width to calculate the
amount of cartesian units that are displayed per pixel.  We then determine
where the x and y axis lie in the pixel range and uses these to compute
the overall x and y offsets from the center of the screen. After that we multiple
the pixel coordinates passed us  minus the computed offset minus the center of the
screen times the scale value.  This gives us the cartesian value that we clicked.
This is then returned frm the function
*/
Complex getViewCoordinates(int x, int y)
{
    Complex xyCoords;
    double newX = 0.0;
    double newY = 0.0;
    double width = 0.0;
    double height = 0.0;
    double yAxis = 0.0;
    double xAxis = 0.0;
    double xOffset = 0.0;
    double yOffset = 0.0;
    double scale = 0.0;

    width = abs(xComplexMax - xComplexMin);
    height = abs(yComplexMax - yComplexMin);

    scale = width / winWidth;

    yAxis = winWidth - (xComplexMax / scale);
    xAxis = winHeight + (yComplexMin / scale);

    xOffset = yAxis - (winWidth / 2);
    yOffset = xAxis - (winHeight / 2);

    newX = (x - xOffset - (winWidth / 2)) * scale;
    newY = ((winHeight / 2) + yOffset - y) * scale;

    xyCoords.x = newX;
    xyCoords.y = newY;

    return xyCoords;
}
#endif
