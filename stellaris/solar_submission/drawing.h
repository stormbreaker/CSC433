#ifndef TDBK_SOLARDRAWING_H
#define TDBK_SOLARDRAWING_H
#include "events.h"
#include "common.h"
#include "planet.h"

/*
    This file simply contains all of the function prototypes for each of the functions
    that are used to draw.  Each function is described in greater detail in the
    drawing.cpp file.  But essentially these are the glut commands that operate
    our program.  
*/

void DrawPlanets();
void DrawPlanet(Planet planet, bool drawRings);
void DrawSun(Planet planet);
void DrawEarth(Planet planet);
void DrawMoon(Planet planet);
void DrawSphere(Planet planet);
void DrawOrbitRing(Planet planet);
void SetColor(int red, int green, int blue);
void DrawStrokeString(string textToPrint, float x, float y, int fontSize);

#endif
