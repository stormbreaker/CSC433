#include "common.h"

// Increment value for the speed of the planets
float AnimateIncrement = 10.0;

//pan and rotation variables
double yRotation = 0;
double xRotation = 15;
double oldX, oldY;
double xPan = 0;
double yPan = 0;
double zoom = -100;

int wireframeSlices = 15;

//flags for states
bool isWireFrame = true;
bool isSmoothShading = false;
bool isLighted = true;
bool isTextured = false;
bool isSingleStep = false;
Texture ringTexture;
