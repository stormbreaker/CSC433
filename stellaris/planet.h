#ifndef TDBK_SOLARPLANET_H
#define TDBK_SOLARPLANET_H

/*
    This file contains all the get and set method declarations for the variables
    for the class and also the private variable declarations along with a few other
    method declarations that are described below.

    The public section contains a constructor of the tank class along with a set
    method for each of the variables declared in the private section. The get
    methods for the private variables are also declared in the public section.
    The two methods incrememtOrbitValues and decrementOrbitValues are declared in
    the public section and are essential in giving each planet the ability to
    orbit and rotate. Finally the getHourOfDay and getDayOfYear method help the
    draw methods know where to put the planets in the rotation around the sun.
*/

#include "glutdefine.h"
#include "common.h"
#include <string>
#include <iostream>

using namespace std;

class Planet
{
    public:
        Planet();

        // Set methods for the properties
        void setRadius(double radius);
        void setName(string name);
        void setPlanetColor(Color planetColor);
        void setDistance(double distance);
        void setYear(double year);
        void setDay(double day);

        void setTexture(Texture texture);

        // Get methods for the properties
        double getRadius();
        string getName();
        Color getPlanetColor();
        double getDistance();
        double getYear();
        double getDay();

        Texture getTexture();

        // Methods that pertain to the orbit and rotation of the planet
        void incrememtOrbitValues();
        void decrementOrbitValues();
        double getHourOfDay();
        double getDayOfYear();


    private:
        // Variable declarations for each variable needed for the planet
        string _Name;
        Texture _Texture;
        Color _PlanetColor;
        int _longitudeSliceCount;
        int _latitudeSliceCount;
        double _Radius;
        double _Distance;
        double _Year;
        double _Day;
        double _HourOfDay;
        double _DayOfYear;
};

#endif
