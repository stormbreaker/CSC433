#ifndef TDBK_COLORS_H
#define TDBK_COLORS_H

#include <vector>

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

void NextColorSet();
void GenerateColorSets();
vector<Color> GetCurrentColorSet();

#endif
