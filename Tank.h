#include <iostream>
#include <vector>
#include "Common.cpp"

using namespace std;

#ifndef Tank_H
#define Tank_H

class Tank
{
    public:
        Tank();

        void SetTankCoords(int xValue, int yValue, bool isLeftTank);

        double CenterCoords[2];
        vector<Coordinate> DrawCoords;

        double fireAngle;

    private:
        void DrawBarrel(int xValue, int yValue);
};

#endif
