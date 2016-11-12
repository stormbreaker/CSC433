#ifndef TDBK_SOLAR_H
#define TDBK_SOLAR_H

#include "glutdefine.h"
#include "common.h"
#include <iostream>
#include <cstdlib>
#include "planet.h"
#include <vector>
#include "FileHandler.cpp"
#include <string>
#include <iostream>
#include <sstream>

static GLenum spinMode = GL_TRUE;
static GLenum singleStep = GL_FALSE;

static vector<Planet> AllPlanets;

vector<Planet> CollectPlanetData();

void OpenGLInit();
void ResizeWindow(int w, int h);
void Animate();
void keyboard(unsigned char key, int x, int y);
void specialInput(int key, int x, int y);
void DrawPlanet(Planet planet, bool drawRings);
void DrawSphere(Planet planet);

void DrawPlanets();
void DrawSun(Planet planet);
void DrawEarth(Planet planet);
void DrawMoon(Planet planet);

#endif
