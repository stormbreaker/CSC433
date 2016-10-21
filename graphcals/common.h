#ifndef TDBK_COMMON_H

#define TDBK_COMMON_H
#include <iomanip>
#include <iostream>
#include "colors.h"

#include "supercommon.h"

using namespace std;

struct Complex
{
    double x;
    double y;
};

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
const int C_KEY = 67;
const int LOWERCASE_C_KEY = 99;
const int J_KEY = 74;
const int LOWERCASE_J_KEY = 106;
const int R_KEY = 82;
const int LOWERCASE_R_KEY = 114;

extern const double ZOOM_FACTOR;
extern const int PIXEL_PAN;

extern Complex mouseCoords;
extern bool isMouseClicked;

extern bool isMandelbrotSet;

Complex complexSquareSerial(Complex z);
void plotPoint(Complex z);
void zoom(double percentage);
void pan(int xPixOffset, int yPixOffset);
Complex getViewCoordinates(int x, int y);

struct color
{
	double r, g, b;
};

#endif
