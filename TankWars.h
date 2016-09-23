#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include "Common.cpp"
#include "Tank.h"
#include "Terrain.h"
#include <cmath>

using namespace std;
/*
    This file is just the header file to separate out from the TankWars.cpp file.
    It contains all of the function prototypes that will be needed for the main
    functioning of the program.  Each function has their header in the TankWars.cpp
    file.  Brief descriptions are written below.

    The display function is the function used by the OpenGL library and matches
    the function protopye as required for a display callback function.

    The keyboard function is the function used by the OpenGL library.  It matches the
    function prototype as required as required for the keyboard listener callback
    function.

    The specialKeyboard function is teh function used by the OpenGL.  It matches
    the function prototype as required for the special keyboard input listener callback
    function that OpenGL requires.

    The DrawStrokeString function takes a given string and prints it to the graphics
    window starting at the given x and y coordinates with the given fontSize.

    The ResetGame function starts the program over and is used to replay the game
    when one tank has won.

    The MoveTank function moves the current tank around the screen based on
    keyboard input.

    The MoveFiringAngle function changes the angle of the current tank based on
    keyboard input.

    The ModifyTankVelocity function takes a double which tells how much to change
    the velocity value of the current tank.

    The SetTankPosition function takes a tank and the x-coordinate to move to.

    
*/
#ifndef TANKWARS_H
#define TANKWARS_H

void display( void );
void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void reshape(int width, int height);
void DrawStrokeString(string textToPrint, float x, float y, int fontSize);

void ResetGame();
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

void DisplayMenu();
string FormatTankCoords(Tank tank);
string FormatTankVelocity(Tank tank);
string FormatTankAngle(Tank tank, bool isLeftTank);
string FormatTankInfoString(Tank leftTank, Tank rightTank);

#endif
