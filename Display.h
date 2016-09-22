#include "Common.cpp"

#ifndef DISPLAY_TWBKTD
#define DISPLAY_TWBKTD


struct Information
{
    Coordinate position;
    double initialVelocity;
    int degrees;
};

class Display
{
    public:
        Display();

    private:
        Information rightTankInformation;
        Information LeftTankInformation;
};
#endif
