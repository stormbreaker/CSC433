#include "Tank.h"

Tank::Tank()
{

}

void Tank::SetTankCoords(int xValue, int yValue, bool rightTurtle)
{
    coordinate coord;

    CenterCoords[0] = xValue;
    CenterCoords[1] = yValue;

    DrawCoords.clear();

    coord.coordinates[0] = xValue - 40;
    coord.coordinates[1] = yValue + 20;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue - 40;
    coord.coordinates[1] = yValue - 20;
    DrawCoords.push_back(coord);

    // Left Wheel
    coord.coordinates[0] = xValue - 30;
    coord.coordinates[1] = yValue - 20;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue - 30;
    coord.coordinates[1] = yValue - 30;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue - 10;
    coord.coordinates[1] = yValue - 30;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue - 10;
    coord.coordinates[1] = yValue - 20;
    DrawCoords.push_back(coord);
    // End Wheel

    // Right Wheel
    coord.coordinates[0] = xValue + 10;
    coord.coordinates[1] = yValue - 20;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 10;
    coord.coordinates[1] = yValue - 30;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 30;
    coord.coordinates[1] = yValue - 30;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 30;
    coord.coordinates[1] = yValue - 20;
    DrawCoords.push_back(coord);
    // End Wheel

    coord.coordinates[0] = xValue + 40;
    coord.coordinates[1] = yValue - 20;
    DrawCoords.push_back(coord);

    // Barrel Begin
    coord.coordinates[0] = xValue + 40;
    coord.coordinates[1] = yValue + 10;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 50;
    coord.coordinates[1] = yValue + 20;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 60;
    coord.coordinates[1] = yValue + 20;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 65;
    coord.coordinates[1] = yValue + 25;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 45;
    coord.coordinates[1] = yValue + 45;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 40;
    coord.coordinates[1] = yValue + 40;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 40;
    coord.coordinates[1] = yValue + 30;
    DrawCoords.push_back(coord);
    // End Barrel

    coord.coordinates[0] = xValue + 30;
    coord.coordinates[1] = yValue + 20;
    DrawCoords.push_back(coord);

    // Dome Creation
    coord.coordinates[0] = xValue + 20;
    coord.coordinates[1] = yValue + 20;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 20;
    coord.coordinates[1] = yValue + 40;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue - 20;
    coord.coordinates[1] = yValue + 40;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue - 20;
    coord.coordinates[1] = yValue + 20;
    DrawCoords.push_back(coord);
    // End Dome
}
