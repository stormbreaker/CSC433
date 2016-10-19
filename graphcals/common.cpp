
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

complex<double> mouseCoords;
bool isMouseClicked = false;

bool isMandelbrotSet = true;

void plotPoint(complex<double> z)
{
	glBegin(GL_POINTS);
		glVertex2d(z.real(), z.imag());
	glEnd();
}

complex<double> complexSquare(complex<double> z)
{
	complex<double> zSquare;

	zSquare = z * z;

	return zSquare;
}

void zoom(double percentage)
{
		double xOffset, yOffset;

        cout << mouseCoords.real() << " " << mouseCoords.imag() << endl;

		// zoom x
		xComplexMin = xComplexMin + (complexWidth) * percentage;
		xComplexMax = xComplexMax - (complexWidth) * percentage;

		complexWidth = xComplexMax - xComplexMin;

		xOffset = mouseCoords.real() - (xComplexMax - (complexWidth / 2.0));

		//cout << "xOffset: " << xOffset << endl;

		xComplexMin = xComplexMin + xOffset;
		xComplexMax = xComplexMax + xOffset;

		// zoom y
		yComplexMin = yComplexMin + (complexHeight) * percentage;
		yComplexMax = yComplexMax - (complexHeight) * percentage;

		complexHeight = yComplexMax - yComplexMin;

		yOffset = mouseCoords.imag() - (yComplexMax - (complexHeight / 2.0));

		yComplexMin = yComplexMin + yOffset;
		yComplexMax = yComplexMax + yOffset;

		glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();

		gluOrtho2D(xComplexMin, xComplexMax, yComplexMin, yComplexMax);
}

complex<double> getViewCoordinates(int x, int y)
{
    complex<double> xyCoords;
    double newX = 0.0;
    double newY = 0.0;
    double width = 0.0;
    double height = 0.0;
    double yAxis = 0.0;
    double xAxis = 0.0;
    double xOffset = 0.0;
    double yOffset = 0.0;
    double scale = 0.0;

    width = abs(xComplexMin) + abs(xComplexMax);
    height = abs(yComplexMin) + abs(yComplexMax);

    scale = width / winWidth;

	// these need to be figured out differently.... TODO since this is our major problem atm
    yAxis = winWidth -(xComplexMax / scale);
    xAxis = winHeight + (yComplexMin / scale);

	cout << "xAxis: " << xAxis << " yAxis: " << yAxis << endl;

    xOffset = yAxis - (winWidth / 2);
    yOffset = xAxis - (winHeight / 2);

    newX = (x - xOffset - (winWidth / 2)) * scale;
    newY = ((winHeight / 2) + yOffset - y) * scale;

    xyCoords = complex<double>(newX, newY);

    return xyCoords;
}
#endif
