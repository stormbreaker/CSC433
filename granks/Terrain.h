
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include "Common.cpp"

using namespace std;

/*
    This file defines the class which contains all of the data and functions/methods
    which are related to the terrain of the program.  It has four methods including
    the constructor, a generateTerrain method which randomizes the terrain, a
    getTerrainData method which returns a linked list of the coordinates which
    define the terrain, and an initializeTerrain function which sets up the initial
    terrain data points.

    The member variable for this class is private and it is a linked list from the
    STL which holds all of the data which describes the terrain.  

*/

#ifndef TERRAIN_HBK
#define TERRAIN_HBK
class Terrain
{
    public:
        Terrain(double width);
        void generateTerrain(int midPointSplitCount);
        list<Coordinate> getTerrainData();
        void initializeTerrain(double width);

    private:
        list<Coordinate> terrainData;
};

#endif
