#ifndef TDBK_COMMON
#define TDBK_COMMON

#include "common.h"
#include <cmath>

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

bool isMandelbrotSet = true;
bool isParallel = true;
bool isAnimating = false;

void plotPoint(Complex z)
{
	glVertex2d(z.x, z.y);
}

Complex complexSquareSerial(Complex z)
{
	Complex zSquare;

	zSquare.x = (z.x * z.x) - (z.y * z.y);
	zSquare.y = 2 * z.x * z.y;

	return zSquare;
}

void SetColorAndPlot(int maxIter, int interations, Complex zPoint, vector<Color> colorSet)
{
    Color ptColor(0, 0, 0);

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

	glColor3ub(ptColor.red, ptColor.green, ptColor.blue);
	plotPoint(zPoint);
}

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

	// these need to be figured out differently.... TODO since this is our major problem atm
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
