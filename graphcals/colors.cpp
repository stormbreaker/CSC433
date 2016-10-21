#ifndef TDBK_COLORS
#define TDBK_COLORS

#include "colors.h"

// Global variables for help with color picking
vector< vector<Color> > AllColorSets;
int CurrentColorSetIndex = 0;
int NumberOfColorSets = 5;
bool UseRandomColorSet = false;
bool IsZooming = false;

// Current random color set being used
vector<Color> RandomSet;

/*
	Name: GenerateColorSets
	Author: Benjamin Kaiser and Taylor Doell
	Description: This function intializes the color set with 5 colors that
    will be used for showing the mandelbrot and julia set
*/
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

/*
	Name: GetCurrentColorSet
	Author: Benjamin Kaiser and Taylor Doell
	Description: This function checks to see if we are wanting random colors or
    the predefined colors. Also, if the user is zooming in on the set, we don't
    want to change their color to a new color.
*/
vector<Color> GetCurrentColorSet()
{
    vector<Color> colorSet;

    // Check if using a random color set
    if (UseRandomColorSet == false)
    {
        colorSet = AllColorSets[CurrentColorSetIndex];
    }
    else
    {
        // Is user is zooming in, don't change the color set
        if (!IsZooming)
        {
            RandomSet = RandomColorSet();
        }

        colorSet = RandomSet;
    }

    // Return color set to use
    return colorSet;
}

/*
	Name: NextColorSet
	Author: Benjamin Kaiser and Taylor Doell
	Description: This function increments the next color index and then checks
    to make sure we haven't gone over our count of colors and if so, resets the
    color back to the first color in the set.
*/
void NextColorSet()
{
    CurrentColorSetIndex++;

    // Reset to initial color if we have gotten to our color limit
    if (CurrentColorSetIndex == NumberOfColorSets)
    {
        CurrentColorSetIndex = 0;
    }
}

/*
	Name: RandomColorSet
	Author: Benjamin Kaiser and Taylor Doell
	Description: This function puts together a random color based on the colors
    passed back from the GetRandomColor function. Also, this function initializes
    srand with time(0) to get more of a random number
*/
vector<Color> RandomColorSet()
{
    vector<Color> colorSet;

    // Initialize the srand() with time(0) for a random number based on time
    srand(time(0));

    // Create color set by values from the GetRandomColor function
    colorSet.push_back(Color(0, 0, 0));
    colorSet.push_back(GetRandomColor());
    colorSet.push_back(GetRandomColor());
    colorSet.push_back(GetRandomColor());
    colorSet.push_back(GetRandomColor());
    colorSet.push_back(GetRandomColor());
    colorSet.push_back(GetRandomColor());

    return colorSet;
}

/*
	Name: GetRandomColor
	Author: Benjamin Kaiser and Taylor Doell
	Description: This function generates a random color based off of a random
    number between 0 and 255 inclusive.
*/
Color GetRandomColor()
{
    // Generate random values for red blue and green color values
    int red = rand() % 255;
    int green = rand() % 255;
    int blue = rand() % 255;

    return Color(red, green, blue);
}
#endif
