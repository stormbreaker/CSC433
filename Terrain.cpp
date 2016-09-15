#include "Terrain.h"
#include <ctime>

Terrain::Terrain(double width)
{
    srand((double) clock());
    initializeTerrain(width);
    generateTerrain(4);
}

void Terrain::initializeTerrain(double width)
{

    double currentPoint = 0;

    double segmentLength = width/4;

    Coordinate initializationCoordinate;
    initializationCoordinate.coordinates[X_COORD] = currentPoint;
    currentPoint += segmentLength;
    initializationCoordinate.coordinates[Y_COORD] = 25;

    terrainData.push_back(initializationCoordinate);

    initializationCoordinate.coordinates[X_COORD] = currentPoint;
    currentPoint += segmentLength;
    initializationCoordinate.coordinates[Y_COORD] = 25;
    terrainData.push_back(initializationCoordinate);


    initializationCoordinate.coordinates[X_COORD] = currentPoint;
    currentPoint +=segmentLength;
    initializationCoordinate.coordinates[Y_COORD] = 400;

    terrainData.push_back(initializationCoordinate);

    initializationCoordinate.coordinates[X_COORD] = currentPoint;
    currentPoint += segmentLength;
    initializationCoordinate.coordinates[Y_COORD] = 25;

    terrainData.push_back(initializationCoordinate);

    initializationCoordinate.coordinates[X_COORD] = currentPoint;
    initializationCoordinate.coordinates[Y_COORD] = 25;

    terrainData.push_back(initializationCoordinate);

    // for (int index = 0; index <= MAX_X; index += 10)
    // {
    //     Coordinate initializationCoordinate;
    //     initializationCoordinate.coordinates[X_COORD] = index;
    //     initializationCoordinate.coordinates[Y_COORD] = (50 + rand() % (75 - 50 + 1)); //should be a random height
    //     terrainData.push_back(initializationCoordinate);
    // }
}

void Terrain::generateTerrain(int midPointSplitCount)
{
    //base case
    if (midPointSplitCount == 0)
    {
        return;
    }

    // for (list<Coordinate>::iterator it = terrainData.begin(); it != terrainData.end(); it++)
    // {
    //     cout << it->coordinates[X_COORD] << " " << it->coordinates[Y_COORD] << endl;
    // }

    list<Coordinate>::iterator iterator = terrainData.begin();
    iterator = next(iterator, 1);
    for (iterator; iterator != terrainData.end(); ++iterator)//terrainData.size(); index++)
    {
        // cout << iterator->coordinates[X_COORD] << endl;
        list<Coordinate>::iterator temporaryIterator = iterator;
        double yChange = rand() % 21 + (-10);
        double yMidPoint = ((iterator->coordinates[Y_COORD] + next(iterator, -1)->coordinates[Y_COORD])/2) + (rand() % 41 + (-20));
        double xMidPoint = (iterator->coordinates[X_COORD] + next(iterator, -1)->coordinates[X_COORD])/2;
        Coordinate temporaryPoint;
        temporaryPoint.coordinates[X_COORD] = xMidPoint;
        temporaryPoint.coordinates[Y_COORD] = yMidPoint;
        // cout << "IT " << iterator->coordinates[X_COORD] << endl;
        terrainData.insert(temporaryIterator, temporaryPoint);
    }

    generateTerrain(midPointSplitCount - 1);
    // cout << "recursed" << endl;
}

list<Coordinate> Terrain::getTerrainData()
{
    return terrainData;
}
