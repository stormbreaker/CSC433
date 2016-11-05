#include "glutdefine.h"
#include "common.h"
#include <string>

using namespace std;

class Planet
{
    public:
        Planet(string name, double radius, string imagePath = "");

        void setRadius(double radius);
        void setName(string name);
        void setTextureImagePath(string filepath);
        void setPlanetColor(Color planetColor);

        double getRadius();
        string getName();
        string getTextureImagePath();
        Color getPlanetColor();

    private:
        double _Radius;
        string _Name;
        string _TextureImagePath;
        Color _PlanetColor;
};
