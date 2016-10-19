#ifndef TDBK_JULIA_H
#define TDBK_JULIA_H

#include "supercommon.h"
#include <complex>

using namespace std;

void julia(GLint nx, GLint ny, GLint maxIter, complex<double> c);
int juliaSqTransform(complex<double> z0, GLint maxIter);



#endif
