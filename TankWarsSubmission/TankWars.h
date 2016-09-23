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

    The specialKeyboard function is the function used by the OpenGL.  It matches
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

    The SetFireAngle function takes a tank and the angle that needs to be added
    to the passed tank's current firing angle.

    The SetFireCoordinates function takes a tank, and sets up the projectile path
    for that specific tank.

    The FindTankCollision function takes an x and a y value.  It then checks to
    see how close the x and y coordinates are to both of the tanks.  If they're
    within a certain amount, it returns true.

    The FindMountainCollision function takes an x and a y value.  It then checks
    to see how close the x and y coordinates are to  coordinates of the terrain.
    If the y value is within a certain distance, it returns true.

    The SetMaxXY function takes an x and a y value which are the coordinates of the
    screen width and height so that we can keep the aspect ratio on the program
    the same.

    The TerrainYValueAtX function takes an x value and finds the y value of the
    terrain at that given x value.

    The FormatMenu function sets up the text for the controls menu at the top of
    the game.

    The FormatTankCoords function sets up the text for displaying where each of
    the tanks are at.

    The FormatTankAngle functions ets up the text for the displaying where each of
    the tank angles are put.

    The FormatTankInfoString takes both the left and right tank and formats all
    of the tanks' information.  
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

string FormatMenu();
string FormatTankCoords(Tank tank);
string FormatTankVelocity(Tank tank);
string FormatTankAngle(Tank tank, bool isLeftTank);
string FormatTankInfoString(Tank leftTank, Tank rightTank);

#endif
