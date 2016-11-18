#ifndef TDBK_SOLAR_H
#define TDBK_SOLAR_H

#include "common.h"
#include "imagemanip.h"
#include "events.h"
#include "planet.h"

vector<Planet> CollectPlanetData();

void OpenGLInit();
void ResizeWindow(int w, int h);
void Animate();

void makeMenu();
void menuSelection(int value);

void SetColor(int red, int green, int blue);
void DrawPlanet(Planet planet, bool drawRings);
void DrawSphere(Planet planet);
void DrawOrbitRing(Planet planet);

void DrawPlanets();
void DrawSun(Planet planet);
void DrawEarth(Planet planet);
void DrawMoon(Planet planet);

void DrawStrokeString(string textToPrint, float x, float y, int fontSize);



#endif
