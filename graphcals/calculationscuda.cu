#ifndef TDBK_MANDELBROT
#define TDBK_MANDELBROT

#include "calculations.h"
#include <stdio.h>
#include <chrono>

using namespace std;

/*
	Name: complexSquare
	Author: code from book modified by Benjamin Kaiser and Taylor Doell
	Description: This function squares the complex number. This function is tagged
    with __device__ to put the function on the card to allow the cuda card to
    easily call it.
*/
__device__ Complex complexSquare(Complex z)
{
	Complex zSquare;

    // Square the complex number
	zSquare.x = (z.x * z.x) - (z.y * z.y);
	zSquare.y = 2 * z.x * z.y;

	return zSquare;
}

/*
	Name: mandelSqTransform
	Author: code from book modified by Benjamin Kaiser and Taylor Doell
	Description: This function performs the calculations finding how fast the
    point diverges for the mandelbrot set. This function has the __global__ tag
    in order for the cuda card to be able to call this function.
*/
__global__ void mandelSqTransf(int maxIter, WindowInfo windowInfo,  Complex *points, int *iterations)
{
    // Get the current index from the thread and block information
    int index = threadIdx.x + blockIdx.x * blockDim.x;

    // Make sure we are in the contents of the array of points so we don't
    // overstep the bounds
    if (index < windowInfo.arrayLength)
    {
	    int counter = 0;
        Complex z0;
	    Complex z;

        // Set initial points for calculations
	    z.x = 0;
	    z.y = 0;

        z0 = points[index];

        // Loop until point diverges or exceeds 4.0
	    while ((z.x * z.x + z.y * z.y <= 4.0) && (counter < maxIter))
	    {
            // Calculate the complex square and increment each point
		    z = complexSquare(z);
		    z.x += z0.x;
		    z.y += z0.y;
		    counter++; // Increment counter for iterations used
	    }

        // Store the iteration count
	    iterations[index] = counter;
    }
}

/*
	Name: juliaSqTransform
	Author: code from book modified by Benjamin Kaiser and Taylor Doell
	Description: This function uses the point from the mandelbrot set to help
    calculate the julia set and uses that to see how fast the point diverges.
    This function has the __global__ tag in order for the cuda card to be able
    to call this function.
*/
__global__ void juliaSqTransform(int maxIter, WindowInfo windowInfo, Complex c, Complex *points, int *iterations)
{
    // Get the current index from the thread and block information
    int index = threadIdx.x + blockIdx.x * blockDim.x;

    // Make sure we are in the contents of the array of points so we don't
    // overstep the bounds
    if (index < windowInfo.arrayLength)
    {
        int counter = 0;
	    Complex z;

        // Set initial points for calculations
	    z = points[index];

        // Loop until point diverges or exceeds 4.0
	    while ((z.x * z.x + z.y * z.y <= 4.0) && (counter < maxIter))
	    {
		    z = complexSquare(z);
		    z.x += c.x;
		    z.y += c.y;
		    counter++;
	    }

        // Store the iteration count
	    iterations[index] = counter;
    }
}

/*
	Name: calculateSetParallel
	Author: Benjamin Kaiser and Taylor Doell
	Description: This is the main function that handles both the mandelbrot and
    the julia set in parallel. A bool flag tells the function which set to
    calculate. There is an optional parameter that can be used if the julia set
    is the set to calculate. Once the number (iterCount) is found, it does some
    calculations to divide the colors that were provided by the color set. It
    then plots the point.
*/
void calculateSetParallel(int nx, int ny, int maxIter, bool isMandelBrot, Complex c)
{
	Complex z, zIncr;
    int counter = 0;
    int arraySize = nx * ny;
    double realIterator = 0.0;
    double imaginaryIterator = 0.0;

    // Store the winInfo to help with set calculations
    WindowInfo winInfo;
    winInfo.arrayLength = arraySize;
    winInfo.xComplexMin = xComplexMin;
    winInfo.xComplexMax = xComplexMax;
    winInfo.yComplexMin = yComplexMin;
    winInfo.yComplexMax = yComplexMax;

    // Intialize size for the array of points
    int size = arraySize * sizeof(Complex);
    Complex *points = (Complex *)malloc(size);
    Complex *dev_points;
    // Allocate size on the card for the points
    cudaMalloc((void **) &dev_points, size);

    // Intialize size for the array of iteration counts
    int it_size = arraySize * sizeof(int);
    int *iterations = (int *)malloc(it_size);
    int *dev_iterations;
    // Allocate size on the card for the values
    cudaMalloc((void **) &dev_iterations, it_size);

    // Initilize thread and block count
    int nThreads = 1024;
    int nBlocks = (arraySize + nThreads - 1) / nThreads;

    // Calculate the increment values for the loop of points
    zIncr.x = complexWidth / double(nx);
    zIncr.y = complexHeight / double(ny);

    // Loop through to create the points for all the calculations
    for (realIterator = xComplexMin; realIterator < xComplexMax - zIncr.x; realIterator += zIncr.x)
    {
        for (imaginaryIterator = yComplexMin; imaginaryIterator < yComplexMax - zIncr.y; imaginaryIterator += zIncr.y)
    	{
            // Set real and imaginary parts of the point to be calculated
    	    z.x = realIterator;
    	    z.y = imaginaryIterator;

            // Store point
    	    points[counter] = z;

            // Increment counter
    	    counter++;
    	}
    }

    // Copy memory to the device
    cudaMemcpy(dev_points, points, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_iterations, iterations, it_size, cudaMemcpyHostToDevice);

    // Calculate currently selected set on the cuda card
    if (isMandelBrot == true)
    {
        mandelSqTransf<<< nBlocks, nThreads >>>(maxIter, winInfo, dev_points, dev_iterations);
    }
    else
    {
        juliaSqTransform<<< nBlocks, nThreads >>>(maxIter, winInfo, c, dev_points, dev_iterations);
    }

	auto start = chrono::system_clock::now();

    // Copy memory back to get the values
    cudaMemcpy(points, dev_points, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(iterations, dev_iterations, it_size, cudaMemcpyDeviceToHost);

    // Get the current color set to draw the pixels with
    vector<Color> colorSet = GetCurrentColorSet();

	chrono::duration<double> test = chrono::system_clock::now() - start;


	//uncomment the following line to see timing output
	//cout << "Parallel: " << test.count() << " seconds" << endl;

    // Loop through all the points and plot them in the window
    glBegin(GL_POINTS);
        for (int i = 0; i < arraySize; i++)
        {
            Complex point = points[i];
            int iterCount = iterations[i];

            SetColorAndPlot(maxIter, iterCount, point, colorSet);
        }
    glEnd();

    // Free up all the memory
    cudaFree(dev_points);
    cudaFree(dev_iterations);
    free(points);
    free(iterations);
}

#endif
