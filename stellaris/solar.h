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

static float HourOfDay = 0.0;
static float DayOfYear = 0.0;
static float AnimateIncrement = 12.0;

vector<Planet> CollectPlanetData();

void OpenGLInit();
void ResizeWindow(int w, int h);
void Animate();
void keyboard(unsigned char key, int x, int y);
void DrawPlanet(double translateAmount);

void DrawPlanets();
void DrawSun();
void DrawEarth();
void DrawMoon();
void DrawMercury();
void DrawVenus();
void DrawMars();
void DrawJupiter();
void DrawSaturn();
void DrawUranus();
void DrawNeptune();

#endif
