#ifndef TDBK_SOLAREVENTS_H
#define TDBK_SOLAREVENTS_H
#include "common.h"
#include "planet.h"

/*
    This file contains all of the function prototypes for all of the event handler
    functions.  This includes the the keyboard handler the mouse movement and the
    mouse click handlers.  
*/

extern std::vector<Planet> AllPlanets;

void keyboard(unsigned char key, int x, int y);
void specialInput(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);

#endif
