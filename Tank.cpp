#include "Tank.h"

/*
    Name: Tank
    Author: Taylor Doell
    Description:  This function is the constructor for the Tank class.  This class
    contains all of the functionality and data need to create a tank.  The constructor
    takes a boolean flag which tells wether or not the tank we are creating is
    the left tank or not.  If it is, the initial firing angle is set to 45 degrees.
    If it is not, then the initial firing angle is set to 135 degrees (45) degrees
    facing to the left of the screen.  The constructor also sets the intial
    velocity for both tanks to 100 m/s.
*/
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

/*
    Name: SetFireCoords
    Author: Taylor Doell
    Description:  This function is simply a setter function for the private member
    variable _ProjectilePath which contains the data necessary to draw the shooting
    arc from each tank.
*/
void Tank::SetFireCoords(vector<Coordinate> &projectilePath)
{
    // Store projectile coordinates for shooting the bullet
    _ProjectilePath = projectilePath;
}

/*
    Name: GetFireCoords
    Author: Taylor Doell
    Description:  This function is simply a getter function for the private member
    variable _ProjectilePath which contains the data necessary to draw the shooting
    arc from each tank.
*/
vector<Coordinate> Tank::GetFireCoords()
{
    // Return projectile coordinates for shooting the bullet
    return _ProjectilePath;
}

/*
    Name: SetTankCoords
    Author: Taylor Doell
    Description:  This function sets up the body of the tank to be drawn.  It also
    calls the other functions to draw the other parts of the tank.
*/
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

/*
    Name: DrawWheels
    Author; Taylor Doell
    Description:  This function sets up the coordinates to draw the wheels for
    each individual tank.  It puts all of the coordinates into the DrawCoords
    vector which is part of the tank class.
*/
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

/*
    Name: DrawBarrel
    Author: Taylor Doell
    Description:  This function sets up all of the coordinates to draw the barrel
    for each of the tank.  It also adds all of the points defining the barrel into
    the DrawCoords point.
*/
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

/*
    Name: DrawDome
    Author: Taylor Doell
    Description:  This function sets up all of the points which describe a tank's
    dome.  All of the points are pushed into the tank's DrawCoords vector to be
    called later to draw it.  
*/
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
