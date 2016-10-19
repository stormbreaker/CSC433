#ifndef TDBK_MANDELBROT
#define TDBK_MANDELBROT

#include "mandelbrot.h"
#include "common.h"

using namespace std;

int mandelSqTransf(complex<double> z0, GLint maxIter)
{
	//book assigns z0 here but the assignment description says z0 should be 0
	complex<double> z = 0;
	int counter = 0;

	while ((z.real() * z.real() + z.imag() * z.imag() <= 4.0) && (counter < maxIter))
	{
		z = complexSquare(z);
		z += z0;
		counter++;
	}

	return counter;
}

//plots the points out
void mandelbrot (int nx, int ny, int maxIter)
{
	complex<double> z, zIncr;
    vector<Color> colorSet;
    Color ptColor(0, 0, 0);

	int iterCount;

	zIncr = complex<double>(complexWidth/GLdouble(nx), complexHeight/GLdouble(ny));

	double realIterator, imaginaryIterator;

    colorSet = GetCurrentColorSet();

	for (realIterator = xComplexMin; realIterator < xComplexMax; realIterator += zIncr.real())
    {
        for (imaginaryIterator = yComplexMin; imaginaryIterator < yComplexMax; imaginaryIterator += zIncr.imag())
    	{
			z = complex<double>(realIterator, imaginaryIterator);

    		iterCount = mandelSqTransf(z, maxIter);
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
}

#endif
