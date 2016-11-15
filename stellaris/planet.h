#include "glutdefine.h"
#include "common.h"
#include <string>
#include <iostream>

using namespace std;

class Planet
{
    public:
        Planet(string name, double radius, string imagePath = "");
        Planet();

        void setRadius(double radius);
        void setName(string name);
        void setPlanetColor(Color planetColor);
        void setDistance(double distance);
        void setYear(double year);
        void setDay(double day);

		void setTexture(Texture texture);

        double getRadius();
        string getName();
        Color getPlanetColor();
        double getDistance();
        double getYear();
        double getDay();

		Texture getTexture();

        void incrememtOrbitValues();
        double getHourOfDay();
        double getDayOfYear();


    private:
        double _Radius;
        string _Name;
		Texture _Texture;
        Color _PlanetColor;
        int _longitudeSliceCount;
        int _latitudeSliceCount;
        double _Distance;
        double _Year;
        double _Day;
        double _HourOfDay;
        double _DayOfYear;
};
