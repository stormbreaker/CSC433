#ifndef TDBK_SOLAR_H
#define TDBK_SOLAR_H

/*
    This file contains all the method declarations for the solar.cpp file. It
    also contains the includes need to run the program.
*/

#include "common.h"
#include "imagemanip.h"
#include "drawing.h"
#include "events.h"
#include "planet.h"

// OpenGL methods
void OpenGLInit();
void ResizeWindow(int w, int h);
void Animate();

// Menu methods
void makeMenu();
void menuSelection(int value);

// Method to get planet data from file
vector<Planet> CollectPlanetData();

#endif
