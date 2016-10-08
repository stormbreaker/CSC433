#ifndef TDBK_MANDELBROT_H

#define TDBK_MANDELBROT_H

#include "common.cpp"

using namespace std;


int mandelSqTransf(complex<double> z0, GLint maxIter);
void mandelbrot (GLint nx, GLint ny, GLint maxIter);

#endif
