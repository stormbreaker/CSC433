#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include "Common.cpp"
#include "Tank.h"
#include "Terrain.h"
#include <cmath>

#ifndef TANKWARS_H
#define TANKWARS_H

void display( void );
void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void reshape(int width, int height);
void DrawStrokeString(string textToPrint, float x, float y, int fontSize);

void MoveTank(int direction);
void MoveFiringAngle(int direction);
void ModifyTankVelocity(double velocityChange);
void SetTankPosition(Tank &tank, double xCoord);
void SetFireAngle(Tank &tank, double angle);
void SetFireCoordinates(Tank &tank);
bool FindTankCollision(double x, double y);
bool FindMountainCollision(double x, double y);
void SetMaxXY(int width, int height);
double TerrainYValueAtX(double xCoord);

string FormatTankCoords(Tank tank);
string FormatTankVelocity(Tank tank);
string FormatTankAngle(Tank tank, bool isLeftTank);
string FormatTankInfoString(Tank leftTank, Tank rightTank);

#endif
