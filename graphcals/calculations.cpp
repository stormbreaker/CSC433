#ifndef TDBK_MANDELBROT
#define TDBK_MANDELBROT

#include "calculations.h"
#include <chrono>

using namespace std;

int mandelSqTransform(Complex c, int maxIter)
{
	Complex z;
	int counter = 0;

	z.x = 0;
	z.y = 0;

	while ((z.x * z.x + z.y * z.y <= 4.0) && (counter < maxIter))
	{
		z = complexSquareSerial(z);
		z.x += c.x;
		z.y += c.y;
		counter++;
	}

	return counter;
}

int juliaSqTransform(Complex z0, int maxIter, Complex c)
{
    Complex z = z0;
	int counter = 0;

	while ((z.x * z.x + z.y * z.y <= 4.0) && (counter < maxIter))
	{
		z = complexSquareSerial(z);
		z.x += c.x;
		z.y += c.y;
		counter++;
	}
	return counter;
}

//plots the points out
void calculateSet(int nx, int ny, int maxIter, bool isMandelbrot, Complex c)
{
	Complex z, zIncr;
    vector<Color> colorSet;
    Color ptColor(0, 0, 0);

	int iterCount;

	zIncr.x = complexWidth / double(nx);
	zIncr.y = complexHeight / double(ny);

	double realIterator, imaginaryIterator;

    colorSet = GetCurrentColorSet();

	glBegin(GL_POINTS);
	auto start = chrono::system_clock::now();

	for (realIterator = xComplexMin; realIterator < xComplexMax; realIterator += zIncr.x)
    {
        for (imaginaryIterator = yComplexMin; imaginaryIterator < yComplexMax; imaginaryIterator += zIncr.y)
    	{
            z.x = realIterator;
            z.y = imaginaryIterator;

            if (isMandelbrot == true)
            {
                iterCount = mandelSqTransform(z, maxIter);
            }
            else
            {
                iterCount = juliaSqTransform(z, maxIter, c);
            }

    		if (iterCount >= maxIter)
    		{
                ptColor = colorSet[0];
    		}
    		else if (iterCount > (maxIter / 8))
    		{
                ptColor = colorSet[1];
    		}
    		else if (iterCount > (maxIter / 10))
    		{
                ptColor = colorSet[2];
    		}
    		else if (iterCount > (maxIter/20))
    		{
                ptColor = colorSet[3];
    		}
    		else if (iterCount > (maxIter/40))
    		{
                ptColor = colorSet[4];
    		}
    		else if (iterCount > (maxIter/100))
    		{
                ptColor = colorSet[5];
    		}
    		else
    		{
                ptColor = colorSet[6];
    		}

    		glColor3ub(ptColor.red, ptColor.green, ptColor.blue);
    		plotPoint(z);
    	}
    }

	chrono::duration<double> test = chrono::system_clock::now() - start;
	glEnd();
}

#endif
