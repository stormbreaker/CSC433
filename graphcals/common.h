#ifndef TDBK_COMMON_H

#define TDBK_COMMON_H
#include <complex>
#include <iomanip>
#include <iostream>
#ifdef __APPLE__
	#include <GLUT/glut.h> // MacOS include
#elif (__linux__)
	#include <GL/glut.h> // LinuxOS include
#endif

using namespace std;

void plotPoint(complex<double> z);
complex<double> complexSquare(complex<double> z);

#endif
