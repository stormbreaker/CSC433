#ifndef TDBK_SUPER_H
#define TDBK_SUPER_H

/*
    This file just contains the include for glut depending on the platform
    this program is compiled and ran on.
*/

#ifdef __APPLE__
	#include <GLUT/glut.h> // MacOS include
#elif (__linux__)
	#include <GL/glut.h> // LinuxOS include
#endif

#endif
