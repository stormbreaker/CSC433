#include "solar.h"


using namespace std;

int main(int argc, char **argv)
{
    CollectPlanetData();
    // Need to double buffer for animation
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    // Create and position the graphics window
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( 720, 480 );
    glutCreateWindow( "Solar System Demo" );

    // Initialize OpenGL.
    OpenGLInit();

    glutKeyboardFunc(keyboard);

    // Callback for graphics image redrawing
    glutDisplayFunc(Animate);
    glutReshapeFunc(ResizeWindow);

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop();

    return 0;
}

// Initialize OpenGL's rendering modes
void OpenGLInit()
{
    glShadeModel( GL_FLAT );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST );
}

void ResizeWindow(int w, int h)
{
    float aspectRatio;
    h = ( h == 0 ) ? 1 : h;
    w = ( w == 0 ) ? 1 : w;
    glViewport( 0, 0, w, h );	// View port uses whole window
    aspectRatio = ( float ) w / ( float ) h;

    // Set up the projection view matrix (not very well!)
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60.0, aspectRatio, 1.0, 40.0 );

    // Select the Modelview matrix
    glMatrixMode( GL_MODELVIEW );
}

// Animate() handles the animation and the redrawing of the graphics window contents.
void Animate()
{
    // Clear the redering window
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if (spinMode)
    {
        // Update the animation state
        HourOfDay += AnimateIncrement;
        DayOfYear += AnimateIncrement / 24.0;

        HourOfDay = HourOfDay - ( ( int ) ( HourOfDay / 24 ) ) * 24;
        DayOfYear = DayOfYear - ( ( int ) ( DayOfYear / 365 ) ) * 365;
    }

    // Clear the current matrix (Modelview)
    glLoadIdentity();

    // Back off eight units to be able to view from the origin.
    glTranslatef ( 0.0, 0.0, -25.0 );

    // Rotate the plane of the elliptic
    // (rotate the model's plane about the x axis by fifteen degrees)
    glRotatef( 15.0, 1.0, 0.0, 0.0 );

    DrawPlanets();

    // Flush the pipeline, and swap the buffers
    glFlush();
    glutSwapBuffers();

    if (singleStep)
    {
        spinMode = GL_FALSE;
    }

    glutPostRedisplay();		// Request a re-draw for animation purposes
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
        case '+':
            glutPostRedisplay();
            break;
        // anything else redraws window
        default:
            break;
    }
}

void DrawPlanets()
{
    DrawSun();

    glPushMatrix();
    DrawEarth();
    DrawMoon();
    glPopMatrix();

    DrawMercury();
    DrawVenus();
    DrawMars();
    DrawJupiter();
    DrawSaturn();
    DrawUranus();
    DrawNeptune();
}

void DrawPlanet(double translateAmount)
{
    glPushMatrix();
    glRotatef(360.0 * DayOfYear / 365.0, 0.0, 1.0, 0.0);
    //glTranslatef( 6.0, 0.0, 0.0 );
    glTranslatef(translateAmount, 0.0, 0.0);

    glRotatef(360.0 * HourOfDay / 24.0, 0.0, 1.0, 0.0);

    glColor3f(0.2, 0.2, 1.0);
    glutWireSphere(0.4, 15, 15);
    glPopMatrix();
}

void DrawSun()
{
    glColor3f( 1.0, 1.0, 0.0 );
    glutWireSphere( 1.0, 15, 15 );
}

void DrawEarth()
{
    glRotatef( 360.0 * DayOfYear / 365.0, 0.0, 1.0, 0.0 );
    glTranslatef( 4.0, 0.0, 0.0 );
    glPushMatrix();
    // Second, rotate the earth on its axis. Use HourOfDay to determine its rotation.
    glRotatef( 360.0 * HourOfDay / 24.0, 0.0, 1.0, 0.0 );
    // Third, draw the earth as a wireframe sphere.
    glColor3f( 0.2, 0.2, 1.0 );
    glutWireSphere( 0.4, 10, 10 );
    glPopMatrix();
}

void DrawMoon()
{
    glRotatef( 360.0 * 12.0 * DayOfYear / 365.0, 0.0, 1.0, 0.0 );
    glTranslatef( 0.7, 0.0, 0.0 );
    glColor3f( 0.3, 0.7, 0.3 );
    glutWireSphere( 0.1, 5, 5 );
}

void DrawMercury()
{
    DrawPlanet(6.0);
}

void DrawVenus()
{
    DrawPlanet(8.0);
}

void DrawMars()
{
    DrawPlanet(10.0);
}

void DrawJupiter()
{
    DrawPlanet(12.0);
}

void DrawSaturn()
{
    DrawPlanet(14.0);
}

void DrawUranus()
{
    DrawPlanet(16.0);
}

void DrawNeptune()
{
    DrawPlanet(18.0);
}

vector<Planet> CollectPlanetData()
{
    string planetLine;

    string name;
    double radius;
    double distance;
    double year;
    double day;
    string imageFile;
    Color planetColor;

    vector<Planet> planets;

    ifstream fin("planetdata.info");

    if (fin)
    {
        while (fin >> name >> radius >> distance >> year >> day >> imageFile >> planetColor.red >> planetColor.green >> planetColor.blue)
        {
            Planet planet;

            planet.setName(name);
            planet.setRadius(radius);
            planet.setDistance(distance);
            planet.setYear(year);
            planet.setDay(day);
            planet.setTextureImagePath(imageFile);
            planet.setPlanetColor(planetColor);

            planets.push_back(planet);
        }
    }
    else
    {
        cout << "Unable to open planetary information.  Exiting." << endl;
        exit(1);
    }
    
    fin.close();
}
