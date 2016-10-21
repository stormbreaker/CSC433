#include "calculations.h"
#include "common.h"

using namespace std;

// GLdisplay callback
void displayFcn(void)
{
	GLint nx = 1024, ny = 1024, maxIter = 1024;

	glClear(GL_COLOR_BUFFER_BIT);

    if (isMandelbrotSet == true)
    {
        if (isParallel == true)
        {
            calculateSetParallel(nx, ny, maxIter, true);
        }
        else
        {
            calculateSetSerial(nx, ny, maxIter, true);
        }
    }
    else
    {
        if (isParallel == true)
        {
            calculateSetParallel(nx, ny, maxIter, false, mouseCoords);
        }
        else
        {
            calculateSetSerial(nx, ny, maxIter, false, mouseCoords);
        }
    }

	glFlush();
}

void animation(int value)
{
    if (isAnimating == true)
    {
        NextColorSet();
	    glutPostRedisplay();
	    glutTimerFunc(250, animation, 1);
	}
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

void specialInput(int key, int x, int y)
{
	cout << key << endl;
	switch(key)
	{
		case GLUT_KEY_UP:
			pan(0, -PIXEL_PAN);
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			pan(0, PIXEL_PAN);
		    glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			pan(PIXEL_PAN, 0);
            glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:
			pan(-PIXEL_PAN, 0);
            glutPostRedisplay();
			break;
		default:
			break;
	}
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
        // Plus key zooms in
        case PLUS_KEY:
            mouseCoords = getViewCoordinates(x, y);
            zoom(ZOOM_FACTOR);

            IsZooming = true;

            glutPostRedisplay();
            break;
        // minus key zooms out
        case MINUS_KEY:
            mouseCoords = getViewCoordinates(x, y);
            zoom(-ZOOM_FACTOR);

            IsZooming = true;

            glutPostRedisplay();
            break;
        case LOWERCASE_A_KEY:
        case A_KEY:
            isAnimating = !isAnimating;
            IsZooming = false;
            
            if (isAnimating == true)
            {
                glutTimerFunc(100, animation, 1);
            }
            break;
        case LOWERCASE_C_KEY:
        case C_KEY:
            UseRandomColorSet = false;
            IsZooming = false;

            NextColorSet();
            glutPostRedisplay();
            break;
        case LOWERCASE_R_KEY:
        case R_KEY:
            UseRandomColorSet = true;
            IsZooming = false;

            glutPostRedisplay();
            break;
        case LOWERCASE_J_KEY:
        case J_KEY:
            isMandelbrotSet = !isMandelbrotSet;

            mouseCoords = getViewCoordinates(x, y);

            glutPostRedisplay();
            break;
        case LOWERCASE_V_KEY:
        case V_KEY:
            isParallel = !isParallel;
            
            glutPostRedisplay();
            break;
        // anything else redraws window
        default:
            break;
    }
}

void mouse(int button, int state, int x, int y)
{
    if (state == 0)
	{
        mouseCoords = getViewCoordinates(x, y);

		if (button == 3)
		{
			zoom(ZOOM_FACTOR);

			IsZooming = true;

			glutPostRedisplay();
		}
		else if (button == 4)
		{
			zoom(-ZOOM_FACTOR);

			IsZooming = true;

			glutPostRedisplay();
		}
	}
}

void currentMousePosition(int x, int y)
{
    if (isMouseClicked == true)
    {
        //cout << x << " " << y << endl;
    }
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("MandelBrot Set");
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(currentMousePosition);
	glutSpecialFunc(specialInput);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);

    GenerateColorSets();

	glutMainLoop();

	return 0;
}
