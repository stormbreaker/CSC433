#ifndef TDBK_JULIA_H
#define TDBK_JULIA_H

#include "glutdefine.h"
#include "common.h"
#include <complex>

using namespace std;

void julia(GLint nx, GLint ny, GLint maxIter, Complex c);
int juliaSqTransform(Complex z0, GLint maxIter);



#endif
