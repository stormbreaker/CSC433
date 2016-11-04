#ifndef TDBK_SOLAR_H
#define TDBK_SOLAR_H

#include "glutdefine.h"
#include <iostream>
#include <cstdlib>

static GLenum spinMode = GL_TRUE;
static GLenum singleStep = GL_FALSE;

static float HourOfDay = 0.0;
static float DayOfYear = 0.0;
static float AnimateIncrement = 12.0;

void OpenGLInit();
void ResizeWindow(int w, int h);
void Animate();

#endif
