#ifndef TDBK_COMMON_H

#define TDBK_COMMON_H
#include <complex>
#include <iomanip>
#include <iostream>

#include "supercommon.h"

using namespace std;

extern unsigned int winWidth;
extern unsigned int winHeight;
extern double xComplexMin;
extern double xComplexMax;

extern double yComplexMin;
extern double yComplexMax;

extern double complexHeight;
extern double complexWidth;

// Helpful constants for key presses
const int ESC_KEY = 27;
const int SPACE_KEY = 32;
const int PLUS_KEY = 43;
const int MINUS_KEY = 45;

extern int ZoomMagnification;
extern const double ZOOM_FACTOR;

extern double mouseX;
extern double mouseY;
extern bool isMouseClicked;

void plotPoint(complex<double> z);
complex<double> complexSquare(complex<double> z);
complex<double> getViewCoordinates(int x, int y);

struct color
{
	double r, g, b;
};

#endif
