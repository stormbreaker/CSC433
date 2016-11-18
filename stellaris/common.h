#ifndef TDBK_COMMON_H
#define TDBK_COMMON_H
#include <string>
#include "glutdefine.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

/*
    This file contains all of the global variables necessary for the running
    of our program including flags and such.  It also contains two structures
    that we use to nicely package some of our data stuff together. 
*/

// Struct to hold the color values
struct Color
{
    int red;
    int green;
    int blue;
};

// Struct to hold texture information and the texture itself
struct Texture
{
	int height = 0;
	int width = 0;
	std::string path = "";
	unsigned char* imageDataArray = nullptr;
};

// Helpful constants for key presses
const int ESC_KEY = 27;

extern float AnimateIncrement;
extern double yRotation;
extern double xRotation;
extern double oldX, oldY;
extern double xPan;
extern double yPan;
extern double zoom;

extern int wireframeSlices;

extern bool isWireFrame;
extern bool isSmoothShading;
extern bool isLighted;
extern bool isTextured;
extern bool isSingleStep;
extern Texture ringTexture;

#endif
