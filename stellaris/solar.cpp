#include "solar.h"

using namespace std;

bool isWireFrame = true;
bool isSmoothShading = false;
bool isLighted = true;
int yRotation = 0;
int xRotation = 15;
int oldX, oldY;
int xPan = 0;
int yPan = 0;
int zoom = -100;
bool isTextured = false;
bool isSingleStep = false;

int main(int argc, char **argv)
{
    // Need to double buffer for animation
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create and position the graphics window
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(720, 480);
    glutCreateWindow("Solar System Demo");

    // Initialize OpenGL.
    OpenGLInit();

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialInput);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    // Callback for graphics image redrawing
    glutDisplayFunc(Animate);
    glutReshapeFunc(ResizeWindow);

    makeMenu();

    AllPlanets = CollectPlanetData();

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop();

    return 0;
}

void makeMenu()
{
    glutCreateMenu(menuSelection);
    glutAddMenuEntry("T  - Toggle Texture", 0);
    glutAddMenuEntry("W - Toggle Wireframe", 1);
    glutAddMenuEntry("L  - Toggle Lighting", 2);
    glutAddMenuEntry("S  - Toggle Smooth Shading", 3);
    glutAddMenuEntry("A  - Toggle Animation Type", 4);
    glutAddMenuEntry("+  - Increase Animation Step", 5);
    glutAddMenuEntry("-   - Decrease Animation Step", 6);
    glutAddMenuEntry("Rotate Right (Right Arrow)", 7);
    glutAddMenuEntry("Rotate Left (Left Arrow)", 8);
    glutAddMenuEntry("Rotate Up (Up Arrow)", 9);
    glutAddMenuEntry("Rotate Down (Down Arrow)", 10);
    glutAddMenuEntry("Zoom In (Mouse Wheel up)", 11);
    glutAddMenuEntry("Zoom Out (Mouse Wheel down)", 12);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menuSelection(int value)
{
    switch (value)
    {
        case 0:
            keyboard('t', 0, 0);
            break;
        case 1:
            keyboard('w', 0, 0);
            break;
        case 2:
            keyboard('l', 0, 0);
            break;
        case 3:
            keyboard('s', 0, 0);
            break;
        case 4:
            keyboard('a', 0, 0);
            break;
        case 5:
            keyboard('+', 0, 0);
            break;
        case 6:
            keyboard('-', 0, 0);
            break;
        case 7:
            specialInput(GLUT_KEY_RIGHT, 0, 0);
            break;
        case 8:
            specialInput(GLUT_KEY_LEFT, 0, 0);
            break;
        case 9:
            specialInput(GLUT_KEY_UP, 0, 0);
            break;
        case 10:
            specialInput(GLUT_KEY_DOWN, 0, 0);
            break;
        case 11:
            mouse(3, GLUT_DOWN, 0, 0);
            break;
        case 12:
            mouse(4, GLUT_UP, 0, 0);
            break;
        default:
            break;
    }
}

// Initialize OpenGL's rendering modes
void OpenGLInit()
{
    glShadeModel( GL_FLAT );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
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
    glTranslatef(xPan, yPan, zoom);

    // Rotate the plane of the elliptic
    // (rotate the model's plane about the x axis by fifteen degrees)
    glRotatef(yRotation, 0.0, 1.0, 0.0);
    glRotatef(xRotation, 1.0, 0.0, 0.0);

    DrawPlanets();

    // Flush the pipeline, and swap the buffers
    glFlush();
    glutSwapBuffers();

    if (isSingleStep == false)
    {
        glutPostRedisplay();		// Request a re-draw for animation purposes
    }
}

void mouse(int button, int state, int x, int y)
{
    if (button == 3)
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
    if (x < oldX)
    {
        xPan -= 5;
    }
    else if (x > oldX)
    {
        xPan += 5;
    }
    else
    {
        xPan = xPan;
    }
    oldX = x;

    if (y < oldY)
    {
        yPan += 5;
    }
    else if (y > oldY)
    {
        yPan -= 5;
    }
    else
    {
        yPan = yPan;
    }
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
			if (isLighted == true)
			{

			}
			else
			{

			}
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
            if (isSingleStep == false)
            {
                planet.incrememtOrbitValues();
            }

            if (planet.getName() == "Earth")
            {
                DrawOrbitRing(planet);

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

                DrawOrbitRing(planet);
            }
            else
            {
                DrawPlanet(planet, false);

                DrawOrbitRing(planet);
            }
        }

        DrawStrokeString(planet.getName(), planet.getDistance(), -15, 2);
    }
}

void DrawPlanet(Planet planet, bool drawRings)
{
    GLUquadric* diskObject = gluNewQuadric();

    Color planetColor = planet.getPlanetColor();

    glPushMatrix();

    SetColor(planetColor.red, planetColor.green, planetColor.blue);

    glRotatef(360.0 * planet.getDayOfYear() / planet.getYear(), 0.0, 1.0, 0.0);

    glTranslatef(planet.getDistance(), 0.0, 0.0);

    glRotatef(360.0 * planet.getHourOfDay() / planet.getDay(), 0.0, 1.0, 0.0);

    DrawSphere(planet);

    if (drawRings == true)
    {
        diskObject = gluNewQuadric();

        gluCylinder(diskObject, planet.getRadius() + 10, planet.getRadius() + 2, 0, 20, 20);
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

    glEnable(GL_COLOR_MATERIAL);
    float sunEmisison[] = { 1.0, 1.0, 0.0, 1.0 };
    // glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, sunEmisison );
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );
    glColor3ub(sunColor.red, sunColor.green, sunColor.blue);
    glDisable(GL_COLOR_MATERIAL);

    DrawSphere(planet);
}

void DrawEarth(Planet planet)
{
    Color earthColor = planet.getPlanetColor();

    glRotatef( 360.0 * planet.getDayOfYear() / planet.getYear(), 0.0, 1.0, 0.0 );
    glTranslatef( planet.getDistance(), 0.0, 0.0 );
    glPushMatrix();
    // Second, rotate the earth on its axis. Use HourOfDay to determine its yRotation.
    glRotatef( 360.0 * planet.getHourOfDay() / planet.getDay(), 0.0, 1.0, 0.0 );
    // Third, draw the earth as a wireframe sphere.

    SetColor(earthColor.red, earthColor.green, earthColor.blue);

    DrawSphere(planet);

    glPopMatrix();
}

void DrawMoon(Planet planet)
{
    Color moonColor = planet.getPlanetColor();

    glRotatef( 360.0 * 12.0 * planet.getDayOfYear() / planet.getYear(), 0.0, 1.0, 0.0 );
    glTranslatef( planet.getDistance(), 0.0, 0.0 );

    SetColor(moonColor.red, moonColor.green, moonColor.blue);

    DrawSphere(planet);
}

void DrawSphere(Planet planet)
{
    GLUquadric* ball = gluNewQuadric();

    glRotatef(90, 1.0, 0.0, 0.0);


	if (isTextured == true)
	{
		glEnable(GL_TEXTURE_2D);
    	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		gluQuadricNormals(ball, GLU_SMOOTH);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, planet.getTexture().width, planet.getTexture().height, 0, GL_RGB, GL_UNSIGNED_BYTE, planet.getTexture().imageDataArray);
		gluQuadricTexture(ball, GL_TRUE);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}
    if (isWireFrame == true)
    {
        glutWireSphere(planet.getRadius(), 15, 15);
    }
    else
    {
	   gluSphere(ball, planet.getRadius(), 15, 15);
    }
}

void SetColor(int red, int green, int blue)
{
    glEnable(GL_COLOR_MATERIAL);

    glColor3ub(red, green, blue);

    glDisable(GL_COLOR_MATERIAL);
}

void DrawOrbitRing(Planet planet)
{
    float planetEmission[] = {0, 0, 0, 0};
    GLUquadric* diskObject = gluNewQuadric();

    glRotatef(90.0, 1.0, 0.0, 0.0);

    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, planetEmission );
    glColor3ub(255, 255, 255);
    glDisable(GL_COLOR_MATERIAL);

    gluCylinder(diskObject, planet.getDistance(), planet.getDistance() + 0.25, 0, 50, 50);

    glRotatef(-90.0, 1.0, 0.0, 0.0);
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
			Texture texture;

            int rows;
            int cols;
			unsigned char* data;

			imageFile = "texture/" + imageFile;

            planet.setName(name);

            planet.setRadius(radius);
            planet.setDistance(distance);
            planet.setYear(year);
            planet.setDay(day);

            planet.setPlanetColor(planetColor);
            LoadBmpFile(imageFile.c_str(), rows, cols, data);

			texture.path = imageFile;
			texture.height = rows;
			texture.width = cols;
			texture.imageDataArray = data;

			planet.setTexture(texture);

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

void DrawStrokeString(string textToPrint, float x, float y, int fontSize)
{
    // Set font size scaling to change the size
    double fontScaling = fontSize / 100.0;
    glColor3ub(255, 255, 255); // Set text color to white

    // Setup gl for drawing the text
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef( x, y, 0 ); // Set x y position to start text
    glScalef(fontScaling, fontScaling, fontScaling);

    // Loop through characters to print them out
    // Had to do this loop because we are using Glut and not FreeGlut
    for (char character : textToPrint)
    {
        // Not new line character for glut so need to simulate it
        if (character == '\n')
        {
            // Decrement y for the new line
            y -= 25;

            // Need to pop and push a new matrix for
            glPopMatrix();
            glPushMatrix();
            glTranslatef( x, y, 0 ); // Set new position to write
            glScalef(fontScaling, fontScaling, fontScaling); // Scale for font size
        }
        else
        {
            // Draw character to string
            glutStrokeCharacter(GLUT_STROKE_ROMAN, character);
        }
    }

    // Pop last matrix for drawing text
    glPopMatrix();
}
