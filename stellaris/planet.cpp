#include "planet.h"


using namespace std;


Planet::Planet(string name, double radius, string imagePath)
{
    Color tempColor;
    tempColor.red = 0;
    tempColor.green = 0;
    tempColor.blue = 0;
    _Radius = radius;
    _Name = name;
    _Texture.path = imagePath;
	_Texture.imageDataArray = nullptr;
    _PlanetColor = tempColor;
    _HourOfDay = 0;
    _DayOfYear = 0;
}

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

Texture Planet::getTexture()
{
	return _Texture;
}

void Planet::setTexture(Texture texture)
{
	_Texture = texture;
}

void Planet::incrememtOrbitValues()
{
    _HourOfDay += AnimateIncrement;
    _DayOfYear += AnimateIncrement / 24.0;

    _HourOfDay = _HourOfDay - ((int)(_HourOfDay / _Day)) * _Day;
    _DayOfYear = _DayOfYear - ((int)(_DayOfYear / _Year)) * _Year;
}

double Planet::getHourOfDay()
{
    return _HourOfDay;
}

double Planet::getDayOfYear()
{
    return _DayOfYear;
}

void Planet::setRadius(double radius)
{
    _Radius = radius;
}

void Planet::setName(string name)
{
    _Name = name;
}



void Planet::setPlanetColor(Color planetColor)
{
    _PlanetColor = planetColor;
}
void Planet::setDistance(double distance)
{
    _Distance = distance;
}
void Planet::setYear(double year)
{
    _Year = year;
}
void Planet::setDay(double day)
{
    _Day = day;
}

double Planet::getRadius()
{
    return _Radius;
}

string Planet::getName()
{
    return _Name;
}


Color Planet::getPlanetColor()
{
    return _PlanetColor;
}
double Planet::getDistance()
{
    return _Distance;
}
double Planet::getYear()
{
    return _Year;
}
double Planet::getDay()
{
    return _Day;
}
