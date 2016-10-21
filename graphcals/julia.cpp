#ifndef TDBK_JULIA
#define TDBK_JULIA

#include "julia.h"


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

void julia(int nx, int ny, int maxIter, Complex c)
{
    Complex z, zIncr;
    color ptColor;

    int iterCount;


	zIncr.x = complexWidth/double(nx);
	zIncr.y = complexHeight/double(ny);

    double realIterator, imaginaryIterator;

	glBegin(GL_POINTS);
    for (realIterator = xComplexMin; realIterator < xComplexMax; realIterator += zIncr.x)
    {
        for (imaginaryIterator = yComplexMin; imaginaryIterator < yComplexMax; imaginaryIterator += zIncr.y)
        {
			z.x = realIterator;
			z.y = imaginaryIterator;

            iterCount = juliaSqTransform(z, maxIter, c);
            if (iterCount >= maxIter)
            {
                ptColor.r = ptColor.g = ptColor.b = 0.0;
            }
            else if (iterCount > (maxIter / 8))
            {
                ptColor.r = 1.0;
                ptColor.g = .5;
                ptColor.b = 0;
            }
            else if (iterCount > (maxIter / 10))
            {
                ptColor.r = 1.0;
                ptColor.g = ptColor.b = 0;
            }
            else if (iterCount > (maxIter/20))
            {
                ptColor.b = .5;
                ptColor.r = ptColor.g = 0;
            }
            else if (iterCount > (maxIter/40))
            {
                ptColor.r = ptColor.g = 1.0;
                ptColor.b = 0;
            }
            else if (iterCount > (maxIter/100))
            {
                ptColor.r = ptColor.b = 0;
                ptColor.g = .3;
            }
            else
            {
                ptColor.r = 0;
                ptColor.g = ptColor.b = 1;
            }
            glColor3d(ptColor.r, ptColor.g, ptColor.b);
            plotPoint(z);
        }
    }
	glEnd();
}

#endif
