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

	mandelbrot(nx, ny, maxIter);

	// julia(nx, ny, maxIter, c);

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
    cout << "KEY HIT " << key << endl;

    // process keypresses
    switch(key)
    {
        // Escape key quits program
        case ESC_KEY:
            exit(0);
            break;
        // Plus key increases Velocity
        case PLUS_KEY:
            ZoomMagnification += 1;

            cout << "PLUS HIT" << endl;

            glutPostRedisplay();
            break;
        // minus key decreses Velocity
        case MINUS_KEY:
            ZoomMagnification -= 1;

            cout << "MINUS HIT" << endl;

            glutPostRedisplay();
            break;
        case LOWERCASE_C_KEY:
        case C_KEY:
            NextColorSet();
            glutPostRedisplay();
            break;

        // anything else redraws window
        default:
            glutPostRedisplay();
            break;
    }
}

void mouse(int button, int state, int x, int y)
{
    double xOffset;
    double yOffset;

	if (state == 0)
	{

		cout << button << endl;


		complex<double> mouseCoords = getViewCoordinates(x, y);

		mouseX = mouseCoords.real();
		mouseY = mouseCoords.imag();
	
		cout << "x: " << mouseX << " y: " << mouseY << endl;
	
		if (button == 3)
		{
			zoom(ZOOM_FACTOR, mouseCoords.real(), mouseCoords.imag());

			glutPostRedisplay();
		}
		else if (button == 4)
		{
			zoom(-ZOOM_FACTOR, mouseCoords.real(), mouseCoords.imag());

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
