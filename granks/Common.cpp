#ifndef COMMON_TWBKTD
#define COMMON_TWBKTD
/*
    This file just contains all of the globals and constructs that are global to
    the entire program.  It also contains a couple methods that are used to convert
    from radians to degree values and degress to radians.  These are used throughout
    the program.
*/
struct Coordinate
{
    double coordinates[2];
};

// View plane size for the coordinate system
const double ViewplaneSize = 1000.0;

// Angle for computing the angle increment
const double ANGLE_OFFSET = 0.01745329251;

// Values used for calculating the arc
const double PI = 3.14159265359;
const double GRAVITY = 9.81;

// Helpful constants for key presses
const int ESC_KEY = 27;
const int R_KEY = 82;
const int LOWER_R_KEY = 114;
const int SPACE_KEY = 32;
const int PLUS_KEY = 43;
const int MINUS_KEY = 45;

// Helpful index numbers for accesing a 1D array with 2 locations
const int X_COORD = 0;
const int Y_COORD = 1;

// Static screen properties
static int ScreenWidth  = 1080;
static int ScreenHeight = 720;
static int MAX_X = 500;
static int MAX_Y = 500;

/*
    Name: DegreesToRadians
    Author: Taylor Doell
    Description:  This function converts degrees to radians.
*/
static double DegreesToRadians(double degrees)
{
    double radians = 0;

    radians = degrees * PI / 180.0;

    return radians;
}

/*
    Name: RadiansToDegrees
    Author: Taylor Doell
    Description:  This function converts radians to degrees.
*/
static double RadiansToDegrees(double radians)
{
    double degrees = 0;

    degrees = (180.0 / PI) * radians;

    return degrees;
}

#endif
