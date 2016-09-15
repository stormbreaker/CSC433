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

        void SetTankCoords(int xOffset, int yOffset, bool rightTank);

        double CenterCoords[2];
        vector<Coordinate> DrawCoords;
};

#endif
