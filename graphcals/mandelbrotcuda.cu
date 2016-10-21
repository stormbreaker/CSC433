#ifndef TDBK_MANDELBROT
#define TDBK_MANDELBROT

#include "mandelbrot.h"
#include "common.h"
#include <stdio.h>

using namespace std;

__device__ Complex complexSquare(Complex z)
{
	Complex zSquare;

	zSquare.x = (z.x * z.x) - (z.y * z.y);
	zSquare.y = 2 * z.x * z.y;

	return zSquare;
}

__global__ void mandelSqTransf(int maxIter, WindowInfo windowInfo,  Complex *points, int *iterations)
{
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    
    if (index < windowInfo.arrayLength)
    {
	    int counter = 0;
        Complex z0;
	    Complex z;
	    
	    z.x = 0;
	    z.y = 0;
    
        z0 = points[index];

	    while ((z.x * z.x + z.y * z.y <= 4.0) && (counter < maxIter))
	    {
		    z = complexSquare(z);
		    z.x += z0.x;
		    z.y += z0.y;
		    counter++;
	    }
	
	    iterations[index] = counter;
    }
}

//plots the points out
void mandelbrot (int nx, int ny, int maxIter)
{
	Complex z, zIncr;
    int counter = 0;
    int arraySize = nx * ny;
    double realIterator = 0.0;
    double imaginaryIterator = 0.0;
    
    WindowInfo winInfo;
    winInfo.arrayLength = arraySize;
    winInfo.xComplexMin = xComplexMin;
    winInfo.xComplexMax = xComplexMax;
    winInfo.yComplexMin = yComplexMin;
    winInfo.yComplexMax = yComplexMax;
    
    int size = arraySize * sizeof(Complex);
    Complex *points = (Complex *)malloc(size);
    Complex *dev_points;
    cudaMalloc((void **) &dev_points, size);
    
    int it_size = arraySize * sizeof(int);
    int *iterations = (int *)malloc(it_size);
    int *dev_iterations;
    cudaMalloc((void **) &dev_iterations, it_size);
    
    int nThreads = 1024;
    int nBlocks = (arraySize + nThreads - 1) / nThreads;
    
    zIncr.x = complexWidth / double(nx);
    zIncr.y = complexHeight / double(ny);
    
    for (realIterator = xComplexMin; realIterator < xComplexMax - zIncr.x; realIterator += zIncr.x)
    {
        for (imaginaryIterator = yComplexMin; imaginaryIterator < yComplexMax - zIncr.y; imaginaryIterator += zIncr.y)
    	{
    	    z.x = realIterator;
    	    z.y = imaginaryIterator;
    	    
    	    points[counter] = z;
    	    
    	    counter++;
    	}
    }
    
    cudaMemcpy(dev_points, points, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_iterations, iterations, it_size, cudaMemcpyHostToDevice);
    
    mandelSqTransf<<< nBlocks, nThreads >>>(maxIter, winInfo, dev_points, dev_iterations);
    
    cudaMemcpy(points, dev_points, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(iterations, dev_iterations, it_size, cudaMemcpyDeviceToHost);
    
    vector<Color> colorSet = GetCurrentColorSet();
    
    glBegin(GL_POINTS);
        for (int i = 0; i < arraySize; i++)
        {
            Complex point = points[i];
            int iterCount = iterations[i];
            
            SetColorAndPlot(maxIter, iterCount, point, colorSet);
        }
    glEnd();
    
    cudaFree(dev_points);
    cudaFree(dev_iterations);
    free(points);
    free(iterations);
}

#endif