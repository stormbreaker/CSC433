#ifndef TDBK_COLORS_H
#define TDBK_COLORS_H

#include <vector>
#include <cstdlib>
#include <iostream>

/*
    This file contains the prototypes for the colors.cpp.

    This file contains a color struct that has an integer value for the red,
    green and blue pixel values. It also contains a constructor for easy color
    creation.

    Bool values to depict if the user is zooming in the set or if they are using
    a random color set help with returning the correct color set.

    All five functions help in setting the next color set or return a color set
    for the program to use in plotting each point from the sets.
*/

using namespace std;

// Struct for holding the RGB color values
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

// Bools to help with choosing correct color
extern bool UseRandomColorSet;
extern bool IsZooming;

// Functions for choosing next color set or returning a color set
void NextColorSet();
void GenerateColorSets();
Color GetRandomColor();
vector<Color> GetCurrentColorSet();
vector<Color> RandomColorSet();

#endif
