#include <iostream>
#include <iomanip>
#include <cmath>
#include "Constants.cpp"
#include "Tank.h"

#ifdef __APPLE__
	#include <GLUT/glut.h> // MacOS include
#elif __linux__
	#include <GL/glut.h> // LinuxOS include
#endif

using namespace std;

int ScreenWidth  = 500;
int ScreenHeight = 500;
Tank CurrentTank;
Tank RightTank;
Tank LeftTank;

void display( void );
void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);

void MoveTank(int direction);

int main(int argc, char *argv[])
{
    CurrentTank = LeftTank;

    glutInit(&argc, argv);                // initialize GLUT
    glutCreateWindow("Tank Wars");		  // open window and specify title
    glutDisplayFunc(display);			  // display callback: how to redisplay window
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutReshapeWindow(ScreenWidth, ScreenHeight);

    glutMainLoop();

    return 0;
}

void display( void )
{
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D( 0, 100, 0, 100 );

    // Put drawing window here
    // I have set the 2D coords to 100 by 100 but we can change this and will want to

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    // process keypresses
    switch(key)
    {
        case SPACE_KEY:
            // Fire weapon
            cout << "Space" << endl;
            break;
        // Escape key quits program
        case ESC_KEY:
            exit(0);
            break;

        // anything else redraws window
        default:
            glutPostRedisplay();
            break;
    }
}

void specialKeyboard(int key, int x, int y)
{
    // process keypresses
    switch(key)
    {
        case GLUT_KEY_RIGHT:
            // Move tank right
            cout << "Right" << endl;
            MoveTank(GLUT_KEY_RIGHT);
            break;
        case GLUT_KEY_LEFT:
            // Move tank right
            cout << "Left" << endl;
            MoveTank(GLUT_KEY_LEFT);
            break;
        case GLUT_KEY_UP:
            // Move tank right
            cout << "Up" << endl;
            break;
        case GLUT_KEY_DOWN:
            // Move tank right
            cout << "Down" << endl;
            break;

        // anything else redraws window
        default:
            glutPostRedisplay();
            break;
    }
}

void MoveTank(int direction)
{
    if (direction == GLUT_KEY_RIGHT)
    {
        CurrentTank.coords[X_COORD] += 1;
    }
    else if (direction == GLUT_KEY_LEFT)
    {
        CurrentTank.coords[X_COORD] -= 1;
    }
}
