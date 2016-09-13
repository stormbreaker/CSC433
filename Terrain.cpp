#include "Terrain.h"
#include <ctime>

Terrain::Terrain()
{
    initializeTerrain();
    generateTerrain(5);
}

void Terrain::initializeTerrain()
{
    srand((int)clock());


    for (int index = 0; index <= MAX_X; index += 10)
    {
        Coordinate initializationCoordinate;
        initializationCoordinate.coordinates[0] = index;
        initializationCoordinate.coordinates[1] = rand() % 100; //should be a random height
        terrainData.push_back(initializationCoordinate);
    }
}

void Terrain::generateTerrain(int midPointSplitCount)
{
    //base case
    if (midPointSplitCount == 0)
    {
        return;
    }
    vector<Coordinate>::iterator it = terrainData.begin();
    for (int index = 1; index < terrainData.size(); index++)
    {
        it++;
        double yChange = rand() % 21 + (-10);
        double yMidPoint = terrainData[index].coordinates[Y_COORD] - terrainData[index - 1].coordinates[Y_COORD];
        double xMidPoint = terrainData[index].coordinates[X_COORD] - terrainData[index - 1].coordinates[X_COORD];
        double temporaryPoint[2];
        temporaryPoint[X_COORD] = xMidPoint;
        temporaryPoint[Y_COORD] = yMidPoint;
        // terrainData.insert(it, temporaryPoint);
    }
    generateTerrain(midPointSplitCount - 1);
    cout << "recursed" << endl;
}

vector<Coordinate> Terrain::getTerrainData()
{
    return terrainData;
}
