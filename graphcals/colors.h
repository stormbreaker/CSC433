#ifndef TDBK_COLORS_H
#define TDBK_COLORS_H

#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

struct Color
{
    int red;
    int green;
    int blue;

    Color(int r, int g, int b)
    {
        red = r;
        green = g;
        blue = b;
    }
};

extern bool UseRandomColorSet;
extern bool IsZooming;

void NextColorSet();
void GenerateColorSets();
Color GetRandomColor();
vector<Color> GetCurrentColorSet();
vector<Color> RandomColorSet();

#endif
