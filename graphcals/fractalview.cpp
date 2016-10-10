#include "mandelbrot.cpp"
#include "common.cpp"

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

	mandelbrot(nx, ny, maxIter);

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
    cout << "KEY HIT" << endl;

    // process keypresses
    switch(key)
    {
        // Escape key quits program
        case ESC_KEY:
            exit(0);
            break;
        // Plus key increases Velocity
        case PLUS_KEY:
            xComplexMin += .1;
            xComplexMax -= .1;
            yComplexMin += .1;
            yComplexMax -= .1;

            complexWidth = xComplexMax - xComplexMin;
            complexHeight = yComplexMax - yComplexMin;

            cout << "PLUS HIT" << endl;

            glutPostRedisplay();
            break;
        // minus key decreses Velocity
        case MINUS_KEY:
            xComplexMin -= .1;
            xComplexMax += .1;
            yComplexMin -= .1;
            yComplexMax += .1;

            complexWidth = xComplexMax - xComplexMin;
            complexHeight = yComplexMax - yComplexMin;

            cout << "MINUS HIT" << endl;

            glutPostRedisplay();
            break;

        // anything else redraws window
        default:
            glutPostRedisplay();
            break;
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

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);

	glutMainLoop();

	return 0;
}
