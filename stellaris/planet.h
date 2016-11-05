#include "glutdefine.h"
#include "common.h"
#include <string>

using namespace std;

class Planet
{
    public:
        void setRadius(double radius);
        void setName(string name);
        void setTextureImagePath(string filepath);
        void setPlanetColor(Color planetColor);

        Planet();

        double getRadius();
        string getName();
        string getTextureImagePath();
        Color getPlanetColor();


    private:
        double _Radius;
        string _Name;
        string _TextureImagePath;
        Color _PlanetColor;
        int _longitudeSliceCount;
        int _latitudeSliceCount;
        double _distance;
        double _year;
        double _day;
};
