
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

// Helpful constants for key presses
const int ESC_KEY = 27;
const int SPACE_KEY = 32;
const int PLUS_KEY = 43;
const int MINUS_KEY = 45;

int ZoomMagnification = 0;
const double ZOOM_FACTOR = .1;

double mouseX = 0.0;
double mouseY = 0.0;

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

struct color
{
	double r, g, b;
};
#endif
