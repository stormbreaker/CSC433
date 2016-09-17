#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include "Common.cpp"
#include "Tank.h"
#include "Terrain.h"

#ifdef __APPLE__
	#include <GLUT/glut.h> // MacOS include
#elif __linux__
	#include <GL/glut.h> // LinuxOS include
#endif

using namespace std;

bool IsCurrentLeft = true;
Tank RightTank;
Tank LeftTank;

Terrain testTerrain(MAX_X);

void display( void );
void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void reshape(int width, int height);

void MoveTank(int direction);
void SetTankPosition(Tank &tank, int xCoord);
void SetMaxXY(int width, int height);
double GetYValueAtX(double xCoord);

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);                // initialize GLUT
    glutCreateWindow("Tank Wars");		  // open window and specify title
    glutDisplayFunc(display);			  // display callback: how to redisplay window
	glutReshapeFunc( reshape );
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutReshapeWindow(ScreenWidth, ScreenHeight);

    SetMaxXY(ScreenWidth, ScreenHeight);

    testTerrain = Terrain(MAX_X);

    LeftTank.SetTankCoords(100, GetYValueAtX(100), true);
    RightTank.SetTankCoords(1400, GetYValueAtX(1400), false);

    glutMainLoop();

    return 0;
}

void display( void )
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Put drawing window here

	glBegin(GL_LINE_STRIP);
		for (Coordinate point : testTerrain.getTerrainData())
		{
			glVertex2dv(point.coordinates);
			// cout << point.coordinates[0] << " " << point.coordinates[1] << endl;
		}
	glEnd();

    glBegin(GL_LINE_LOOP);
        for (Coordinate xyPair : LeftTank.DrawCoords)
        {
            glVertex2dv(xyPair.coordinates);
        }
    glEnd();

    glBegin(GL_LINE_LOOP);
        for (Coordinate xyPair : RightTank.DrawCoords)
        {
            glVertex2dv(xyPair.coordinates);
        }
    glEnd();

    glFlush();
}

void reshape(int width, int height)
{
    ScreenWidth = width;
    ScreenHeight = height;

    glLoadIdentity();

    SetMaxXY(width, height);

    gluOrtho2D(0, MAX_X, 0, MAX_Y);

    glViewport(0, 0, width, height);
}

void keyboard(unsigned char key, int x, int y)
{
    // process keypresses
    switch(key)
    {
        case SPACE_KEY:
            // Fire weapon
            IsCurrentLeft = !IsCurrentLeft;
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
            MoveTank(GLUT_KEY_RIGHT);
            break;
        case GLUT_KEY_LEFT:
            // Move tank right
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
    double xCoord = 0;

    if (direction == GLUT_KEY_RIGHT)
    {
        xCoord = 10;
    }
    else if (direction == GLUT_KEY_LEFT)
    {
        xCoord = -10;
    }

    if (IsCurrentLeft == true)
    {
        SetTankPosition(LeftTank, xCoord);
    }
    else
    {
        SetTankPosition(RightTank, xCoord);
    }

    glutPostRedisplay();
}

void SetTankPosition(Tank &tank, int xCoord)
{
    xCoord += tank.CenterCoords[X_COORD];

    tank.SetTankCoords(xCoord, GetYValueAtX(xCoord), IsCurrentLeft);

    if (xCoord < 0)
    {
        tank.SetTankCoords(0, GetYValueAtX(0), IsCurrentLeft);
    }
    else if (xCoord > MAX_X)
    {
        tank.SetTankCoords(MAX_X, GetYValueAtX(MAX_X), IsCurrentLeft);
    }
}

void SetMaxXY(int width, int height)
{
    if (width > height)
    {
        MAX_X = ViewplaneSize * width / height;
        MAX_Y = ViewplaneSize;
    }
    else
    {
        MAX_X = ViewplaneSize;
        MAX_Y = ViewplaneSize * width / height;
    }
}

double GetYValueAtX(double xValue)
{
    double y = 0;
    double m = 0;
    double x = 0;
    double b = 0;
    double yCoord = 0;
    Coordinate firstPoint;

    for (Coordinate coords : testTerrain.getTerrainData())
    {
        if (coords.coordinates[X_COORD] > xValue)
        {
            x = coords.coordinates[X_COORD];
            y = coords.coordinates[Y_COORD];

            m = coords.coordinates[Y_COORD] - firstPoint.coordinates[Y_COORD];
            m /= coords.coordinates[X_COORD] - firstPoint.coordinates[X_COORD];

            b = y - m * x;

            yCoord = m * xValue + b + 10;

            break;
        }

        firstPoint = coords;
    }

    return yCoord;
}
