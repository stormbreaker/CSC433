#ifndef TDBK_MANDELBROT_H

#define TDBK_MANDELBROT_H

//#include "common.h"

#include <complex>

#include "glutdefine.h"
#include "common.h"

using namespace std;


int mandelSqTransf(Complex z0, int maxIter);
void mandelbrot (int nx, int ny, int maxIter);

#endif
