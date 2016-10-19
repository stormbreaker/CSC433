#ifndef TDBK_COLORS
#define TDBK_COLORS

#include "colors.h"

vector< vector<Color> > AllColorSets;
int CurrentColorSetIndex = 0;
int NumberOfColorSets = 5;
bool UseRandomColorSet = false;

void GenerateColorSets()
{
    vector<Color> colorSet;

    colorSet.push_back(Color(0, 0, 0));
    colorSet.push_back(Color(255, 128, 0));
    colorSet.push_back(Color(255, 0, 0));
    colorSet.push_back(Color(128, 0, 0));
    colorSet.push_back(Color(255, 255, 0));
    colorSet.push_back(Color(0, 77, 0));
    colorSet.push_back(Color(0, 255, 255));

    AllColorSets.push_back(colorSet);
    colorSet.clear();

    colorSet.push_back(Color(0, 0, 0));
    colorSet.push_back(Color(255, 198, 26));
    colorSet.push_back(Color(255, 184, 77));
    colorSet.push_back(Color(255, 153, 0));
    colorSet.push_back(Color(230, 138, 0));
    colorSet.push_back(Color(255, 0, 0));
    colorSet.push_back(Color(205, 10, 10));

    AllColorSets.push_back(colorSet);
    colorSet.clear();

    colorSet.push_back(Color(0, 0, 0));
    colorSet.push_back(Color(255, 198, 26));
    colorSet.push_back(Color(255, 184, 77));
    colorSet.push_back(Color(255, 255, 179));
    colorSet.push_back(Color(255, 255, 230));
    colorSet.push_back(Color(102, 181, 255));
    colorSet.push_back(Color(51, 156, 255));

    AllColorSets.push_back(colorSet);
    colorSet.clear();

    colorSet.push_back(Color(0, 0, 0));
    colorSet.push_back(Color(255, 51, 0));
    colorSet.push_back(Color(51, 204, 51));
    colorSet.push_back(Color(0, 204, 153));
    colorSet.push_back(Color(51, 204, 204));
    colorSet.push_back(Color(0, 102, 255));
    colorSet.push_back(Color(102, 153, 255));

    AllColorSets.push_back(colorSet);
    colorSet.clear();

    colorSet.push_back(Color(0, 0, 0));
    colorSet.push_back(Color(255, 255, 0));
    colorSet.push_back(Color(102, 204, 255));
    colorSet.push_back(Color(255, 102, 0));
    colorSet.push_back(Color(204, 102, 255));
    colorSet.push_back(Color(0, 115, 230));
    colorSet.push_back(Color(0, 89, 179));

    AllColorSets.push_back(colorSet);
}

vector<Color> GetCurrentColorSet()
{
    vector<Color> colorSet;

    if (UseRandomColorSet == false)
    {
        colorSet = AllColorSets[CurrentColorSetIndex];
    }
    else
    {
        colorSet = RandomColorSet();

        UseRandomColorSet = false;
    }

    return colorSet;
}

void NextColorSet()
{
    CurrentColorSetIndex++;

    if (CurrentColorSetIndex == NumberOfColorSets)
    {
        CurrentColorSetIndex = 0;
    }
}

vector<Color> RandomColorSet()
{
    vector<Color> colorSet;

    srand(time(0));

    colorSet.push_back(Color(0, 0, 0));
    colorSet.push_back(GetRandomColor());
    colorSet.push_back(GetRandomColor());
    colorSet.push_back(GetRandomColor());
    colorSet.push_back(GetRandomColor());
    colorSet.push_back(GetRandomColor());
    colorSet.push_back(GetRandomColor());

    return colorSet;
}

Color GetRandomColor()
{
    int red = rand() % 255;
    int green = rand() % 255;
    int blue = rand() % 255;

    return Color(red, green, blue);
}
#endif
