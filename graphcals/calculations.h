#ifndef TDBK_MANDELBROT_H

#define TDBK_MANDELBROT_H

/*
    This file contains the prototypes for the calculation functions.

    The two calculate functions for serial and parallel both have an optional
    parameter that is used in calculating the Julia set. Each set is
    calculated the same except for point c is used for incrementation in the
    Julia set. There is a parallel and serial version depending on which type
    the user has chosen by pressing V.
*/

#include <complex>
#include "glutdefine.h"
#include "common.h"

using namespace std;

int mandelSqTransf(Complex z0, GLint maxIter);

// Functions used for calculating the functions in parallel and serial
void calculateSetSerial(int nx, int ny, int maxIter, bool isMandelbrot, Complex c = Complex());
void calculateSetParallel(int nx, int ny, int maxIter, bool isMandelBrot, Complex c = Complex());

#endif
