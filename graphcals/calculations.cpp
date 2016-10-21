#ifndef TDBK_MANDELBROT
#define TDBK_MANDELBROT

#include "calculations.h"
#include <chrono>

using namespace std;

/*
	Name: mandelSqTransform
	Author: code from book modified by Benjamin Kaiser and Taylor Doell
	Description: This function performs the calculations finding how fast the
    point diverges for the mandelbrot set.
*/
int mandelSqTransform(Complex c, int maxIter)
{
	Complex z;
	int counter = 0;

    // Set initial points for calculations
	z.x = 0;
	z.y = 0;

    // Loop until point diverges or exceeds 4.0
	while ((z.x * z.x + z.y * z.y <= 4.0) && (counter < maxIter))
	{
        // Calculate the complex square and increment each point
		z = complexSquareSerial(z);
		z.x += c.x;
		z.y += c.y;
		counter++; // Increment counter for iterations used
	}

    // Return increment count
	return counter;
}

/*
	Name: juliaSqTransform
	Author: code from book modified by Benjamin Kaiser and Taylor Doell
	Description: This function uses the point from the mandelbrot set to help
    calculate the julia set and uses that to see how fast the point diverges.
*/
int juliaSqTransform(Complex z0, int maxIter, Complex c)
{
    // Setup point for calculation
    Complex z = z0;
	int counter = 0;

    // Loop until the point diverges or until 4.0
	while ((z.x * z.x + z.y * z.y <= 4.0) && (counter < maxIter))
	{
        // Compute the complex square and increment by the c value
		z = complexSquareSerial(z);
		z.x += c.x;
		z.y += c.y;
		counter++; // Increment iteration count
	}

    // return iteration count
	return counter;
}

/*
	Name: calculateSetSerial
	Author: Benjamin Kaiser and Taylor Doell
	Description: This is the main function that handles both the mandelbrot and
    the julia set in serial. A bool flag tells the function which set to calculate. There
    is an optional parameter that can be used if the julia set is the set to
    calculate. Once the number (iterCount) is found, it does some calculations to
    divide the colors that were provided by the color set. It then plots the
    point.
*/
void calculateSetSerial(int nx, int ny, int maxIter, bool isMandelbrot, Complex c)
{
    int iterCount;
	Complex z, zIncr;
    vector<Color> colorSet;
    Color ptColor(0, 0, 0);
    double realIterator, imaginaryIterator;

    // Calculate the increment values
	zIncr.x = complexWidth / double(nx);
	zIncr.y = complexHeight / double(ny);

    // Get the current color set to draw
    colorSet = GetCurrentColorSet();

	glBegin(GL_POINTS);
    	auto start = chrono::system_clock::now();

        // Loop through all the points and calculate the values for the set
    	for (realIterator = xComplexMin; realIterator < xComplexMax; realIterator += zIncr.x)
        {
            for (imaginaryIterator = yComplexMin; imaginaryIterator < yComplexMax; imaginaryIterator += zIncr.y)
        	{
                // Set the next point in the calculation
                z.x = realIterator;
                z.y = imaginaryIterator;

                // Calculate set depending on currently selected set
                if (isMandelbrot == true)
                {
                    iterCount = mandelSqTransform(z, maxIter);
                }
                else
                {
                    iterCount = juliaSqTransform(z, maxIter, c);
                }

                // Check max iterations and the iteration count to choose color
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

                // Set current color and plot point
        		glColor3ub(ptColor.red, ptColor.green, ptColor.blue);
        		plotPoint(z);
        	}
        }

    	chrono::duration<double> test = chrono::system_clock::now() - start;
	glEnd();
}

#endif
