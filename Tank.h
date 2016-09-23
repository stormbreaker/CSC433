#include <iostream>
#include <vector>
#include "Common.cpp"

using namespace std;

#ifndef Tank_H
#define Tank_H
/*
    This file contains all of the variables and methods which manipulate all of
    the data which is related to a single tank object.

    The public section contains a constructor of the tank class.  It takes a boolean
    flag which indicates whether or not the tank to be created is the left tank
    on the screen.  The public section also contains a public method called
    SetTankCoords which will go through the entire tank and sets the coords to the
    new position of the tank.
    The class also contains a method called SetFireCoords which takes a vector of
    coordinates which will describe the path of a projectile fired by this tank
    if one has been fired.

    Theere is also a public method called GetFireCoords which simply returns
    the vector of coordinates which describes the path of a projectile fired from
    this instance of the tank.

    The class has a double array of length two which contains the information of
    the tanks center coordinates.  This member variable is called CenterCoords.

    The class also has a vector of coordinates called DrawCoords which contains
    all of the coordinates describing the outline of the tank.

    The FireAngle member variable, we are treating similar to a C# property.  This
    variable contains the data in radians of what angle the tank should fire at.

    The Velocity member variable, we are also treating as similar to a C# property.
    This variable contains the data in meters per second of the firing velocity
    of the current instance of the tank.

    In the private section of this class, there is a single member variable and
    three functions.  The member variable is the _ProjectilePath which contains
    all of the actualdata for the path a projectile takes when the tank fires.

    The three functions all pretty much serve a similar purpose.  The functions
    are called DrawBarrel, DrawWheels, and DrawDome.  These are used
    by the SetTankCoords to add data into the DrawCoords variable.  
*/

class Tank
{
    public:
        Tank(bool isLeft);

        void SetTankCoords(int xValue, int yValue, bool isLeftTank);
        void SetFireCoords(vector<Coordinate> &projectilePath);
        vector<Coordinate> GetFireCoords();

        double CenterCoords[2];
        vector<Coordinate> DrawCoords;

        double FireAngle;

        double Velocity;

    private:
        vector<Coordinate> _ProjectilePath;

        void DrawBarrel(int xValue, int yValue);
        void DrawWheels(int xValue, int yValue);
        void DrawDome(int xValue, int yValue);
};

#endif
