#include <iostream>
#include <iomanip>
#include <cmath>
#ifdef __APPLE__
	#define MACOS
#elif __linux__
	#define LINUX
#endif

#ifdef MACOS
	#include <GLUT/glut.h> //MacOS include?
#else
	#include <GL/glut.h> //LinuxOS include
#endif

using namespace std;

// global vars
int ScreenWidth  = 500;
int ScreenHeight = 500;

void display( void );

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);                // initialize GLUT
    glutCreateWindow("Tank Wards");		  // open window and specify title
    glutDisplayFunc(display);			  // display callback: how to redisplay window
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
