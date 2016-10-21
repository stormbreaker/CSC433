#ifndef TDBK_JULIA_H
#define TDBK_JULIA_H

#include "glutdefine.h"
#include "common.h"

using namespace std;

void julia(int nx, int ny, int maxIter, Complex c);
int juliaSqTransform(Complex z0, int maxIter);

#endif
