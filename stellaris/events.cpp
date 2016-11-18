#include "events.h"

std::vector<Planet> AllPlanets;

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        oldX = x;
        oldY = y;
    }
    else if (button == 3)
    {
        zoom += 10;
    }
    else if (button == 4)
    {
        zoom -= 10;
    }
}

void mouseMotion(int x, int y)
{
    double xDiff = (x - oldX) / 4;
    double yDiff = (y - oldY) / 4;

    xPan += xDiff;
    yPan -= yDiff;

    oldX = x;
    oldY = y;
}

void keyboard(unsigned char key, int x, int y)
{
    // process keypresses
    switch(key)
    {
        // Escape key quits program
        case ESC_KEY:
            exit(0);
            break;
        case 'A':
        case 'a':
            isSingleStep = !isSingleStep;

            if (isSingleStep == false)
            {
                glutPostRedisplay();
            }
            break;
        // Change the shading model
        case 'S':
        case 's':
            // Toggle if smooth shading is enabled
            isSmoothShading = !isSmoothShading;

            // Change shading model
            if (isSmoothShading == true)
            {
                glShadeModel( GL_SMOOTH );
            }
            else
            {
                glShadeModel( GL_FLAT );
            }

            glutPostRedisplay();
            break;
        // Change if planets are wireframe
        case 'W':
        case 'w':
            // Toggle wireframe display
            isWireFrame = !isWireFrame;

            glutPostRedisplay();
            break;
        // Plus key zooms in
        case '+':
            if (isSingleStep == false)
            {
                AnimateIncrement += 5;
            }
            else
            {
                for (Planet &planet : AllPlanets)
                {
                    planet.incrememtOrbitValues();
                }
            }

            glutPostRedisplay();
            break;
        case '-':
            if (isSingleStep == false)
            {
                AnimateIncrement -= 5;
            }
            else
            {
                for (Planet &planet : AllPlanets)
                {
                    planet.decrementOrbitValues();
                }
            }

            glutPostRedisplay();
            break;
		case 'L':
		case 'l':
			isLighted = !isLighted;
			if (isLighted == true)
			{
    		    glEnable( GL_LIGHTING );
    			glEnable( GL_LIGHT0 );
			}
            else
            {
                glDisable(GL_LIGHTING);
                glDisable(GL_LIGHT0);
            }
			break;
		case 'T':
		case 't':
			isTextured = !isTextured;
			break;
        // anything else redraws window
        default:
            break;
    }
}

/*
	Name: specialInput
	Author: Benjamin Kaiser and Taylor Doell
	Description: This function handles the special keys for the keyboard. It is
    used for catching the arrow keys for panning the solar system.
*/
void specialInput(int key, int x, int y)
{
    // Find key used
	switch(key)
	{
        // Pan up the solar system
		case GLUT_KEY_UP:
            xRotation += 3;
			glutPostRedisplay();
			break;
        // Pan down the solar system
		case GLUT_KEY_DOWN:
            xRotation -= 3;
		    glutPostRedisplay();
			break;
        // Pan the solar system to the right
		case GLUT_KEY_RIGHT:
            yRotation += 3;
            glutPostRedisplay();
			break;
        // Pan the solar system to the left
		case GLUT_KEY_LEFT:
            yRotation -= 3;
            glutPostRedisplay();
			break;
		default:
			break;
	}
}
