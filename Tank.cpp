#include "Tank.h"

Tank::Tank(bool isLeft)
{
    // Check which tank to set correct starting firing angles
	if (isLeft)
	{
	    fireAngle = DegreesToRadians(45);
	}
	else
	{
		fireAngle = DegreesToRadians(135);
	}

    // Set initial velocity to 100 for the tanks
    velocity = 100;
}

void Tank::SetFireCoords(vector<Coordinate> &projectilePath)
{
    // Store projectile coordinates for shooting the bullet
    _ProjectilePath = projectilePath;
}

vector<Coordinate> Tank::GetFireCoords()
{
    // Return projectile coordinates for shooting the bullet
    return _ProjectilePath;
}

void Tank::SetTankCoords(int xValue, int yValue, bool isLeftTank)
{
    double scale = 0.35;
    Coordinate coord;

    // Record the center coordinates of the tank
    CenterCoords[X_COORD] = xValue;
    CenterCoords[Y_COORD] = yValue;

    // Clear all existing coords
    DrawCoords.clear();

    // Draw back side of tank
    coord.coordinates[X_COORD] = -40 * scale;
    coord.coordinates[Y_COORD] = yValue + 20 * scale;
    DrawCoords.push_back(coord);

    coord.coordinates[X_COORD] = -40 * scale;
    coord.coordinates[Y_COORD] = yValue - 20 * scale;
    DrawCoords.push_back(coord);

    // Draw Wheels
    DrawWheels(xValue, yValue);

    // Draw Front side of tank
    coord.coordinates[X_COORD] = 40 * scale;
    coord.coordinates[Y_COORD] = yValue - 20 * scale;
    DrawCoords.push_back(coord);

    // Draw the Barrel
    DrawBarrel(xValue, yValue);

    // Draw the connection point between barrel and dome
    coord.coordinates[X_COORD] = 30 * scale;
    coord.coordinates[Y_COORD] = yValue + 20 * scale;
    DrawCoords.push_back(coord);

    // Draw the tank dome
    DrawDome(xValue, yValue);

    // Checking if Right or Left Tank
    if (isLeftTank == false)
    {
        // Loop through coords add xValue to offset the coords
        // Also multiply the X_COORD values by -1 to change tank direction
        for (Coordinate &coordinate : DrawCoords)
        {
            coordinate.coordinates[X_COORD] = coordinate.coordinates[X_COORD] * -1 + xValue;
        }
    }
    else
    {
        // Loop through coords add xValue to offset the coords
        for (Coordinate &coordinate : DrawCoords)
        {
            coordinate.coordinates[X_COORD] += xValue;
        }
    }
}

void Tank::DrawWheels(int xValue, int yValue)
{
    // Scale variable for easier math coordinates
    double scale = 0.35;
    Coordinate coord;

    // Set coordinates for the Left Wheel
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

    // Set coordinates for the Right Wheel
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
}

void Tank::DrawBarrel(int xValue, int yValue)
{
    // Scale variable for easier math coordinates
    double scale = 0.35;
    Coordinate coord;

    // Set coordinates for the Barrel of the tank
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

void Tank::DrawDome(int xValue, int yValue)
{
    // Scale variable for easier math coordinates
    double scale = 0.35;
    Coordinate coord;

    // Set coordinates for the dome of the tank
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
}
