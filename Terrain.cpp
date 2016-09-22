#include "Terrain.h"
#include <ctime>
/*
	Name: Terrain
	Author: Benjamin Kaiser
	Description:  This function is the constructor for the class which contains
    all of the terrain data and associated functionality.  It takes a width which
    is the width of the screen at the time the terrain was generated.  It then seeds
    the random number generator with the current system time.  It then calls the
    initializeTerrain function which lays out the base shape of the terrain.
    Then it calls the generateTerrain function with 4 levels of recursion.
*/
Terrain::Terrain(double width)
{
    srand((double) clock());
    initializeTerrain(width);
    generateTerrain(4);
}

/*
	Name: initializeTerrain
	Author: Benjamin Kaiser
	Description:  This function initializes the terrain with the basic shape of
    the terrain as prescribed by Dr. Weiss.  This is two flat sides with a mountain
    in the middle.  Overall, there are 5 initial points created.  These are stored
    in the class' terrainData member function and the y coordinate of these points
    are hardcoded in.  The function takes a width which is the width of the screen
    at the time this function is called, and can dynamically calculate the x coordinate
    of each initial point by taking that width and dividing it by the number of initial
    line segments there are (4).  Each of these are then pushed into a linked list
    provided by the C++ STL library.
*/
void Terrain::initializeTerrain(double width)
{

    double currentPoint = 0; //current x value of the current point

    double segmentLength = width/4;

    Coordinate initializationCoordinate;

	//left side
    initializationCoordinate.coordinates[X_COORD] = currentPoint;
    currentPoint += segmentLength;
    initializationCoordinate.coordinates[Y_COORD] = 200;
    terrainData.push_back(initializationCoordinate);

	//left side of mountain
    initializationCoordinate.coordinates[X_COORD] = currentPoint;
    currentPoint += segmentLength;
    initializationCoordinate.coordinates[Y_COORD] = 200;
    terrainData.push_back(initializationCoordinate);


	//top of mountain
    initializationCoordinate.coordinates[X_COORD] = currentPoint;
    currentPoint +=segmentLength;
    initializationCoordinate.coordinates[Y_COORD] = 600;
    terrainData.push_back(initializationCoordinate);

	//right side of mountain
    initializationCoordinate.coordinates[X_COORD] = currentPoint;
    currentPoint += segmentLength;
    initializationCoordinate.coordinates[Y_COORD] = 200;
    terrainData.push_back(initializationCoordinate);

	//right side
    initializationCoordinate.coordinates[X_COORD] = currentPoint;
    initializationCoordinate.coordinates[Y_COORD] = 200;
	terrainData.push_back(initializationCoordinate);
}

/*
	Name: generateTerrain
	Author: Benjamin Kaiser
	Description:  This function is the recursive midpoint displacement function
    described by Dr. Weiss in class to generate the terrain for the TankWars Program.
    The function takes an integer value which acts as the number of levels of recursion
    to go through (in other words, how many times to split each initial line segment).
    The base case is when this value reaches 0.  Otherwise, the midpoint of each line
    segment is found using the midpoint formula and the y value is randomly generated
    between -20 to 20.  This value is then added to the current value to determine the
    new y value of the line segment.
*/
void Terrain::generateTerrain(int midPointSplitCount)
{
    //base case
    if (midPointSplitCount == 0)
    {
        return;
    }

	//set up the iteration through the list
    list<Coordinate>::iterator iterator = terrainData.begin();
    list<Coordinate>::iterator endIterator = terrainData.begin();
    endIterator = prev(iterator, 1);
    iterator = next(iterator, 1);

	//iterate through the list and displace point
    for (iterator; iterator != endIterator; ++iterator)
    {
        list<Coordinate>::iterator temporaryIterator = iterator;
        double yMidPoint = ((iterator->coordinates[Y_COORD] + next(iterator, -1)->coordinates[Y_COORD])/2) + (rand() % 41 + (-20));
        double xMidPoint = (iterator->coordinates[X_COORD] + next(iterator, -1)->coordinates[X_COORD])/2;
        Coordinate temporaryPoint;
        temporaryPoint.coordinates[X_COORD] = xMidPoint;
        temporaryPoint.coordinates[Y_COORD] = yMidPoint;

		//insert new displaced point
        terrainData.insert(temporaryIterator, temporaryPoint);
    }

	//recurse down to next level
    generateTerrain(midPointSplitCount - 1);
}

/*
    Name: getTerrainData
    Author: Benjamin Kaiser
    Description: This function is literally just a getter function for the private
    terrainData linked list in the Terrain class.  
*/
list<Coordinate> Terrain::getTerrainData()
{
    return terrainData;
}
