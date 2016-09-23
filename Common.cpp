#ifndef COMMON_TWBKTD
#define COMMON_TWBKTD

struct Coordinate
{
    double coordinates[2];
};

const double ViewplaneSize = 1000.0;

const double ANGLE_OFFSET = 0.01745329251;

const double PI = 3.14159265359;
const double GRAVITY = 9.81;

const int ESC_KEY = 27;
const int R_KEY = 82;
const int LOWER_R_KEY = 114;
const int SPACE_KEY = 32;
const int PLUS_KEY = 43;
const int MINUS_KEY = 45;
const int X_COORD = 0;
const int Y_COORD = 1;

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
