#include "glutdefine.h"
#include "common.h"
#include <string>

using namespace std;

class Planet
{
    public:
        Planet(string name, double radius, string imagePath = "");
        Planet();

        void setRadius(double radius);
        void setName(string name);
        void setTextureImagePath(string filepath);
        void setPlanetColor(Color planetColor);
        void setDistance(double distance);
        void setYear(double year);
        void setDay(double day);

        double getRadius();
        string getName();
        string getTextureImagePath();
        Color getPlanetColor();
        double getDistance();
        double getYear();
        double getDay();

    private:
        double _Radius;
        string _Name;
        string _TextureImagePath;
        Color _PlanetColor;
        int _longitudeSliceCount;
        int _latitudeSliceCount;
        double _Distance;
        double _Year;
        double _Day;
};
