#include <iostream>
#include <vector>
#include <list>
#include "Common.cpp"

using namespace std;

#ifndef TERRAIN_HBK
#define TERRAIN_HBK
class Terrain
{
    public:
        Terrain();
        void generateTerrain(int midPointSplitCount);
        list<Coordinate> getTerrainData();
        void initializeTerrain();

    private:
        list<Coordinate> terrainData;
};

#endif
