#include "Tank.h"

Tank::Tank()
{

}

void Tank::SetTankCoords(int xValue, int yValue, bool rightTank)
{
    double scale = 0.35;
    Coordinate coord;

    CenterCoords[0] = xValue;
    CenterCoords[1] = yValue;

    DrawCoords.clear();

    coord.coordinates[0] = xValue - 40 * scale;
    coord.coordinates[1] = yValue + 20 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue - 40 * scale;
    coord.coordinates[1] = yValue - 20 * scale;
    DrawCoords.push_back(coord);

    // Left Wheel
    coord.coordinates[0] = xValue - 30 * scale;
    coord.coordinates[1] = yValue - 20 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue - 30 * scale;
    coord.coordinates[1] = yValue - 30 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue - 10 * scale;
    coord.coordinates[1] = yValue - 30 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue - 10 * scale;
    coord.coordinates[1] = yValue - 20 * scale;
    DrawCoords.push_back(coord);
    // End Wheel

    // Right Wheel
    coord.coordinates[0] = xValue + 10 * scale;
    coord.coordinates[1] = yValue - 20 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 10 * scale;
    coord.coordinates[1] = yValue - 30 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 30 * scale;
    coord.coordinates[1] = yValue - 30 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 30 * scale;
    coord.coordinates[1] = yValue - 20 * scale;
    DrawCoords.push_back(coord);
    // End Wheel

    coord.coordinates[0] = xValue + 40 * scale;
    coord.coordinates[1] = yValue - 20 * scale;
    DrawCoords.push_back(coord);

    // Barrel Begin
    coord.coordinates[0] = xValue + 40 * scale;
    coord.coordinates[1] = yValue + 10 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 50 * scale;
    coord.coordinates[1] = yValue + 20 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 60 * scale;
    coord.coordinates[1] = yValue + 20 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 65 * scale;
    coord.coordinates[1] = yValue + 25 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 45 * scale;
    coord.coordinates[1] = yValue + 45 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 40 * scale;
    coord.coordinates[1] = yValue + 40 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 40 * scale;
    coord.coordinates[1] = yValue + 30 * scale;
    DrawCoords.push_back(coord);
    // End Barrel

    coord.coordinates[0] = xValue + 30 * scale;
    coord.coordinates[1] = yValue + 20 * scale;
    DrawCoords.push_back(coord);

    // Dome Creation
    coord.coordinates[0] = xValue + 20 * scale;
    coord.coordinates[1] = yValue + 20 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue + 20 * scale;
    coord.coordinates[1] = yValue + 40 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue - 20 * scale;
    coord.coordinates[1] = yValue + 40 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[0] = xValue - 20 * scale;
    coord.coordinates[1] = yValue + 20 * scale;
    DrawCoords.push_back(coord);
    // End Dome
}
