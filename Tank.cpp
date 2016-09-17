#include "Tank.h"

Tank::Tank()
{
    fireAngle = 0.0;
}

void Tank::SetTankCoords(int xValue, int yValue, bool isLeftTank)
{
    double scale = 0.35;
    Coordinate coord;

    CenterCoords[X_COORD] = xValue;
    CenterCoords[Y_COORD] = yValue;

    DrawCoords.clear();

    coord.coordinates[X_COORD] = -40 * scale;
    coord.coordinates[Y_COORD] = yValue + 20 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = -40 * scale;
    coord.coordinates[Y_COORD] = yValue - 20 * scale;
    DrawCoords.push_back(coord);

    // Left Wheel
    coord.coordinates[X_COORD] = -30 * scale;
    coord.coordinates[Y_COORD] = yValue - 20 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = -30 * scale;
    coord.coordinates[Y_COORD] = yValue - 30 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = -10 * scale;
    coord.coordinates[Y_COORD] = yValue - 30 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = -10 * scale;
    coord.coordinates[Y_COORD] = yValue - 20 * scale;
    DrawCoords.push_back(coord);
    // End Wheel

    // Right Wheel
    coord.coordinates[X_COORD] = 10 * scale;
    coord.coordinates[Y_COORD] = yValue - 20 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = 10 * scale;
    coord.coordinates[Y_COORD] = yValue - 30 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = 30 * scale;
    coord.coordinates[Y_COORD] = yValue - 30 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = 30 * scale;
    coord.coordinates[Y_COORD] = yValue - 20 * scale;
    DrawCoords.push_back(coord);
    // End Wheel

    coord.coordinates[X_COORD] = 40 * scale;
    coord.coordinates[Y_COORD] = yValue - 20 * scale;
    DrawCoords.push_back(coord);

    DrawBarrel(xValue, yValue);

    coord.coordinates[X_COORD] = 30 * scale;
    coord.coordinates[Y_COORD] = yValue + 20 * scale;
    DrawCoords.push_back(coord);

    // Dome Creation
    coord.coordinates[X_COORD] = 20 * scale;
    coord.coordinates[Y_COORD] = yValue + 20 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = 20 * scale;
    coord.coordinates[Y_COORD] = yValue + 40 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = -20 * scale;
    coord.coordinates[Y_COORD] = yValue + 40 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = -20 * scale;
    coord.coordinates[Y_COORD] = yValue + 20 * scale;
    DrawCoords.push_back(coord);
    // End Dome

    if (isLeftTank == false)
    {
        for (Coordinate &coordinate : DrawCoords)
        {
            coordinate.coordinates[X_COORD] = coordinate.coordinates[X_COORD] * -1 + xValue;
        }
    }
    else
    {
        for (Coordinate &coordinate : DrawCoords)
        {
            coordinate.coordinates[X_COORD] += xValue;
        }
    }
}

void Tank::DrawBarrel(int xValue, int yValue)
{
    double scale = 0.35;
    Coordinate coord;

    coord.coordinates[X_COORD] = 40 * scale;
    coord.coordinates[Y_COORD] = yValue + 10 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = 50 * scale;
    coord.coordinates[Y_COORD] = yValue + 20 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = 60 * scale;
    coord.coordinates[Y_COORD] = yValue + 20 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = 65 * scale;
    coord.coordinates[Y_COORD] = yValue + 25 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = 45 * scale;
    coord.coordinates[Y_COORD] = yValue + 45 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = 40 * scale;
    coord.coordinates[Y_COORD] = yValue + 40 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = 40 * scale;
    coord.coordinates[Y_COORD] = yValue + 30 * scale;
    DrawCoords.push_back(coord);
}
