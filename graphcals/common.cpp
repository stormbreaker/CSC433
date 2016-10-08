
#ifndef TDBK_COMMON
#define TDBK_COMMON

#include "common.h"

unsigned int winWidth = 500;
unsigned int winHeight = 500;

double xComplexMin = -2.00, xComplexMax = .50;
double yComplexMin = -1.25, yComplexMax = 1.25;

double complexWidth = xComplexMax - xComplexMin;
double complexHeight = yComplexMax - yComplexMin;

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
	GLdouble r, g, b;
};

#endif
