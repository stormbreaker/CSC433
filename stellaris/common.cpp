#include "common.h"

// Increment value for the speed of the planets
float AnimateIncrement = 10.0;


double yRotation = 0;
double xRotation = 15;
double oldX, oldY;
double xPan = 0;
double yPan = 0;
double zoom = -100;

bool isWireFrame = true;
bool isSmoothShading = false;
bool isLighted = true;
bool isTextured = false;
bool isSingleStep = false;
Texture ringTexture;
