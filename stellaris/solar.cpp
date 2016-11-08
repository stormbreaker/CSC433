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

    AllPlanets = CollectPlanetData();

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
    gluPerspective( 60.0, aspectRatio, 1.0, 1000.0 );

    // Select the Modelview matrix
    glMatrixMode( GL_MODELVIEW );
}

// Animate() handles the animation and the redrawing of the graphics window contents.
void Animate()
{
    // Clear the rendering window
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Clear the current matrix (Modelview)
    glLoadIdentity();

    // Back off eight units to be able to view from the origin.
    glTranslatef ( 0.0, 0.0, -100.0 );

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
    for (Planet &planet : AllPlanets)
    {
        if (planet.getName() == "Sun")
        {
            DrawSun(planet);
        }
        else
        {
            if (spinMode)
            {
                planet.incrememtOrbitValues();
            }

            if (planet.getName() == "Earth")
            {
                glPushMatrix();
                DrawEarth(planet);
            }
            else if (planet.getName() == "Moon")
            {
                DrawMoon(planet);
                glPopMatrix();
            }
            else if (planet.getName() == "Saturn")
            {
                DrawPlanet(planet, true);
            }
            else
            {
                DrawPlanet(planet, false);
            }
        }
    }
}

void DrawPlanet(Planet planet, bool drawRings)
{
    Color planetColor = planet.getPlanetColor();

    glPushMatrix();

    glRotatef(360.0 * planet.getDayOfYear() / planet.getYear(), 0.0, 1.0, 0.0);

    glTranslatef(planet.getDistance(), 0.0, 0.0);

    glRotatef(360.0 * planet.getHourOfDay() / planet.getDay(), 0.0, 1.0, 0.0);
    glEnable(GL_COLOR_MATERIAL);
    float planetEmission[] = {0, 0, 0, 0};
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, planetEmission );
    glColor3ub(planetColor.red, planetColor.green, planetColor.blue);
    glDisable(GL_COLOR_MATERIAL);
    glutWireSphere(planet.getRadius(), 15, 15);

    if (drawRings == true)
    {
        GLUquadric* diskObject = gluNewQuadric();

        glRotatef(90.0, 1.0, 0.0, 0.0);

        gluDisk(diskObject, planet.getRadius() + 2, 20, 50, 20);
    }

    glPopMatrix();
}

void DrawSun(Planet planet)
{
    Color sunColor = planet.getPlanetColor();

    float light_position[] = { 0, 0, 0, 1.0 };
    float light_ambient[] = { 0.01, 0.01, 0.01, 1.0 };       // ambient light
    float light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };       // diffuse light
    float light_specular[] = { 1.0, 1.0, 1.0, 1.0 };      // highlights

    // glEnd();
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    glEnable(GL_COLOR_MATERIAL);
    float sunEmisison[] = { 1.0, 1.0, 0.0, 1.0 };
    // glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, sunEmisison );
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );
    glColor3ub(sunColor.red, sunColor.green, sunColor.blue);

    // glDisable(GL_COLOR_MATERIAL);
     // enable one light source
     glDisable(GL_COLOR_MATERIAL);

    glutWireSphere(planet.getRadius(), 15, 15);
}

void DrawEarth(Planet planet)
{
    Color earthColor = planet.getPlanetColor();

    glRotatef( 360.0 * planet.getDayOfYear() / planet.getYear(), 0.0, 1.0, 0.0 );
    glTranslatef( planet.getDistance(), 0.0, 0.0 );
    glPushMatrix();
    // Second, rotate the earth on its axis. Use HourOfDay to determine its rotation.
    glRotatef( 360.0 * planet.getHourOfDay() / planet.getDay(), 0.0, 1.0, 0.0 );
    // Third, draw the earth as a wireframe sphere.
    glEnable(GL_COLOR_MATERIAL);
    glColor3ub( earthColor.red, earthColor.green, earthColor.blue );
    glDisable(GL_COLOR_MATERIAL);

    glutWireSphere( planet.getRadius(), 10, 10 );
    glPopMatrix();
}

void DrawMoon(Planet planet)
{
    Color moonColor = planet.getPlanetColor();

    glRotatef( 360.0 * 12.0 * planet.getDayOfYear() / planet.getYear(), 0.0, 1.0, 0.0 );
    glTranslatef( planet.getDistance(), 0.0, 0.0 );
    glEnable(GL_COLOR_MATERIAL);
    glColor3ub( moonColor.red, moonColor.green, moonColor.blue );
    glDisable(GL_COLOR_MATERIAL);

    glutWireSphere( planet.getRadius(), 5, 5 );
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
    return planets;
}
