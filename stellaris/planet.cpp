#include "planet.h"
#include "glutdefine.h"
#include "common.h"
#include <string>

using namespace std;

class Planet
{
    public:
        void setRadius(double radius);
        void setName(string name);
        void setTextureImage(string filepath);
        void setPlanetColor(Color planetColor);

        double getRadius();
        string getName();
        string getTextureImage();
        Color getPlanetColor();


    private:
        double radius;
        string name;
        string textureImage;
        Color planetColor;
};
