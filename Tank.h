#include <iostream>
#include <vector>
#include "Common.cpp"

using namespace std;

#ifndef Tank_H
#define Tank_H

class Tank
{
    public:
        Tank(bool isLeft);

        void SetTankCoords(int xValue, int yValue, bool isLeftTank);
        void SetFireCoords(vector<Coordinate> &projectilePath);
        vector<Coordinate> GetFireCoords();

        double CenterCoords[2];
        vector<Coordinate> DrawCoords;

        double fireAngle;

        double velocity;

    private:
        vector<Coordinate> _ProjectilePath;

        void DrawBarrel(int xValue, int yValue);
};

#endif
