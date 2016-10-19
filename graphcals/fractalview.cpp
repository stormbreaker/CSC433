#include "mandelbrot.h"
#include "common.h"
#include "julia.h"

using namespace std;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// GLdisplay callback
void displayFcn(void)
{
	GLint nx = 1000, ny = 1000, maxIter = 1000;

	glClear(GL_COLOR_BUFFER_BIT);

	complex<double> c(.353,.288);

    if (isMandelbrotSet == true)
    {
        mandelbrot(nx, ny, maxIter);
    }
    else
    {
        cout << mouseCoords.real() << " " << mouseCoords.imag() << endl;

        julia(nx, ny, maxIter, mouseCoords);
    }

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

            cout << "PLUS HIT" << endl;

            glutPostRedisplay();
            break;
        // minus key zooms out
        case MINUS_KEY:
            mouseCoords = getViewCoordinates(x, y);

            zoom(-ZOOM_FACTOR);

            cout << "MINUS HIT" << endl;

            glutPostRedisplay();
            break;
        case LOWERCASE_C_KEY:
        case C_KEY:
            NextColorSet();
            glutPostRedisplay();
            break;
        case LOWERCASE_R_KEY:
        case R_KEY:
            UseRandomColorSet = true;
            NextColorSet();
            glutPostRedisplay();
            break;
        case LOWERCASE_J_KEY:
        case J_KEY:
            isMandelbrotSet = !isMandelbrotSet;

            mouseCoords = getViewCoordinates(x, y);

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

			glutPostRedisplay();
		}
		else if (button == 4)
		{
			zoom(-ZOOM_FACTOR);

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

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);

    GenerateColorSets();

	glutMainLoop();

	return 0;
}
