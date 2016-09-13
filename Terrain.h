#include <iostream>
#include <vector>
#include "Common.cpp"

using namespace std;

#ifndef TERRAIN_HBK
#define TERRAIN_HBK
class Terrain
{
    public:
        Terrain();
        void generateTerrain(int midPointSplitCount);
        vector<Coordinate> getTerrainData();
        void initializeTerrain();

    private:
        vector<Coordinate> terrainData;
};

#endif
