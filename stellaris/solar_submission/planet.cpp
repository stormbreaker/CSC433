#include "planet.h"

/*
    This file contains all the method implementations that are declared in the
    class header file. This provides a nice way for each planet to be separate
    and store the information when loaded from the planetdata.info file. It holds
    the color of the planet, the texture of the planet, ways to access those
    properties and the ability to incrememt or decrement the orbit values to allow
    single step increment.
*/

using namespace std;

/*
    Name: Planet Constructor
    Author: Benjamin Kaiser and Taylor Doell
    Description:  This is the constructor for the planet class. It's main purpose
    is to initialize the class properties to their default values.
*/
Planet::Planet()
{
    Color tempColor;
    _PlanetColor.red = 1;
    _PlanetColor.green = 1;
    _PlanetColor.blue = 1;
    _Radius = 1;
    _Name = "";
    _Texture.path = "";
    _Texture.imageDataArray = nullptr;
    _HourOfDay = 0;
    _DayOfYear = 0;
}

/*
    Name: incrememtOrbitValues
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Increments orbit values to allow the planet to orbit around
    the sun.
*/
void Planet::incrememtOrbitValues()
{
    // Increment hour of day and day of year for orbit animation computed by
    // the scale of earth days for day of year
    _HourOfDay += AnimateIncrement;
    _DayOfYear += AnimateIncrement / 24.0;

    // Calculate new hour of day and day of year values for orbit animation
    _HourOfDay = _HourOfDay - ((int)(_HourOfDay / _Day)) * _Day;
    _DayOfYear = _DayOfYear - ((int)(_DayOfYear / _Year)) * _Year;
}

/*
    Name: decrementOrbitValues
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Decrements orbit values to allow for single step ability.
*/
void Planet::decrementOrbitValues()
{
    // Decrement hour of day and day of year for orbit animation computed by
    // the scale of earth days for day of year
    _HourOfDay -= AnimateIncrement;
    _DayOfYear -= AnimateIncrement / 24.0;

    // Calculate new hour of day and day of year values for orbit animation
    _HourOfDay = _HourOfDay - ((int)(_HourOfDay / _Day)) * _Day;
    _DayOfYear = _DayOfYear - ((int)(_DayOfYear / _Year)) * _Year;
}

/*
    Name: getHourOfDay
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Accessor method for the hour of day value
*/
double Planet::getHourOfDay()
{
    return _HourOfDay;
}

/*
    Name: getDayOfYear
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Accessor method for the day of year value
*/
double Planet::getDayOfYear()
{
    return _DayOfYear;
}

/*
    Name: getTexture
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Accessor method for the texture
*/
Texture Planet::getTexture()
{
    return _Texture;
}

/*
    Name: setTexture
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Setter method for the texture
*/
void Planet::setTexture(Texture texture)
{
    _Texture = texture;
}

/*
    Name: getRadius
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Accessor method for the radius of the planet
*/
double Planet::getRadius()
{
    return _Radius;
}

/*
    Name: setRadius
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Setter method for the radius of the planet
*/
void Planet::setRadius(double radius)
{
    _Radius = radius;
}

/*
    Name: getName
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Accessor method for the name of the planet
*/
string Planet::getName()
{
    return _Name;
}

/*
    Name: setName
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Setter method for the name of the planet
*/
void Planet::setName(string name)
{
    _Name = name;
}

/*
    Name: getPlanetColor
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Accessor method for the planet color
*/
Color Planet::getPlanetColor()
{
    return _PlanetColor;
}

/*
    Name: setPlanetColor
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Setter method for the planet color
*/
void Planet::setPlanetColor(Color planetColor)
{
    _PlanetColor = planetColor;
}

/*
    Name: getDistance
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Accessor method for the distance from the sun
*/
double Planet::getDistance()
{
    return _Distance;
}

/*
    Name: setDistance
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Setter method for the distance from the sun
*/
void Planet::setDistance(double distance)
{
    _Distance = distance;
}

/*
    Name: getYear
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Accessor method for the year value
*/
double Planet::getYear()
{
    return _Year;
}

/*
    Name: setYear
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Setter method for the year value
*/
void Planet::setYear(double year)
{
    _Year = year;
}

/*
    Name: getDay
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Accessor method for the day value
*/
double Planet::getDay()
{
    return _Day;
}

/*
    Name: setDay
    Author: Benjamin Kaiser and Taylor Doell
    Description:  Setter method for the day value
*/
void Planet::setDay(double day)
{
    _Day = day;
}
