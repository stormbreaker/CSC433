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
const int SPACE_KEY = 32;
const int PLUS_KEY = 43;
const int MINUS_KEY = 45;
const int X_COORD = 0;
const int Y_COORD = 1;

static int ScreenWidth  = 1080;
static int ScreenHeight = 720;

static int MAX_X = 500;
static int MAX_Y = 500;

static double DegreesToRadians(double degrees)
{
    double radians = 0;

    radians = degrees * PI / 180.0;

    return radians;
}

static double RadiansToDegrees(double radians)
{
    double degrees = 0;

    degrees = (180.0 / PI) * radians;

    return degrees;
}

#endif
