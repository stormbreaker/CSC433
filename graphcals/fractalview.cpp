#ifdef __APPLE__
	#include <GLUT/glut.h> // MacOS include
#elif (__linux__)
	#include <GL/glut.h> // LinuxOS include
#endif

#include "mandelbrot.h"
// #include "common.cpp"

using namespace std;

GLdouble xComplexMin = -2.00, xComplexMax = .50;
GLdouble yComplexMin = -1.25, yComplexMax = 1.25;

GLdouble complexWidth = xComplexMax - xComplexMin;
GLdouble complexHeight = yComplexMax - yComplexMin;

struct color
{
	GLdouble r, g, b;
};

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void plotPoint(complex<double> z)
{
	glBegin(GL_POINTS);
		glVertex2d(z.real(), z.imag());
	glEnd();
}

complex<double> complexSquare(complex<double> z)
{
	complex<double> zSquare;

	zSquare = z * z;

	return zSquare;
}


GLint mandelSqTransf(complex<double> z0, GLint maxIter)
{
	complex<double> z = z0;
	GLint counter = 0;

	while ((z.real() * z.real() + z.imag() * z.imag() <= 4.0) && (counter < maxIter))
	{
		z = complexSquare(z);
		z += z0;
		counter++;
	}
	return counter;
}

//plots the points out
void mandelbrot (GLint nx, GLint ny, GLint maxIter)
{
	complex<double> z, zIncr;
	color ptColor;

	GLint iterCount;

	zIncr = complex<double>(complexWidth/GLdouble(nx), complexHeight/GLdouble(ny));

	double realIterator, imaginaryIterator;

	for (realIterator = xComplexMin; realIterator < xComplexMax; realIterator += zIncr.real())
    {
        for (imaginaryIterator = yComplexMin; imaginaryIterator < yComplexMax; imaginaryIterator += zIncr.imag())
    	{
			z = complex<double>(realIterator, imaginaryIterator);
    		iterCount = mandelSqTransf(z, maxIter);
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

// GLdisplay callback
void displayFcn(void)
{
	GLint nx = 1000, ny = 1000, maxIter = 1000;

	glClear(GL_COLOR_BUFFER_BIT);

	mandelbrot (nx, ny, maxIter);
	glFlush();
}

// GLwindow reshape callback
void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newHeight, newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(xComplexMin, xComplexMax, yComplexMin, yComplexMax);

	glClear(GL_COLOR_BUFFER_BIT);
}


int main(int argc, char** argv)
{


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("MandelBrot Set");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);

	glutMainLoop();

	return 0;
}
