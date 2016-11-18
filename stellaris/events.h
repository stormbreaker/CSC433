#ifndef TDBK_SOLAREVENTS_H
#define TDBK_SOLAREVENTS_H
#include "common.h"
#include "planet.h"

extern std::vector<Planet> AllPlanets;

void keyboard(unsigned char key, int x, int y);
void specialInput(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);

#endif
