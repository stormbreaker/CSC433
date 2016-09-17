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

        void SetTankCoords(int xOffset, int yOffset, bool isLeftTank);

        double CenterCoords[2];
        vector<Coordinate> DrawCoords;

    private:
        void DrawBarrel(int xValue, int yValue);
};

#endif
