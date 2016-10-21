#ifndef TDBK_JULIA
#define TDBK_JULIA

#include "julia.h"
#include "common.h"

__device__ Complex complexSquare(Complex z)
{
	Complex zSquare;

	zSquare.x = (z.x * z.x) - (z.y * z.y);
	zSquare.y = 2 * z.x * z.y;

	return zSquare;
}

int juliaSqTransform(Complex z0, GLint maxIter, Complex c)
{
    Complex z = z0;
	int counter = 0;

	while ((z.real() * z.real() + z.imag() * z.imag() <= 4.0) && (counter < maxIter))
	{
		z = complexSquare(z);
		z += c;
		counter++;
	}
	return counter;
}

void julia(GLint nx, GLint ny, GLint maxIter, Complex c)
{
    Complex z, zIncr;
    color ptColor;

    int iterCount;

    zIncr = Complex(complexWidth/GLdouble(nx), complexHeight/GLdouble(ny));

    double realIterator, imaginaryIterator;

    for (realIterator = xComplexMin; realIterator < xComplexMax; realIterator += zIncr.real())
    {
        for (imaginaryIterator = yComplexMin; imaginaryIterator < yComplexMax; imaginaryIterator += zIncr.imag())
        {
            z = Complex(realIterator, imaginaryIterator);

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
}

#endif
