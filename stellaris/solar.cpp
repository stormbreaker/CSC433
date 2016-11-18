/*
    CSC 433 - Computer Graphics
    Dr. John Weiss
    Programming Assignment #3 - Solar System
    Benjamin Kaiser and Taylor Doell
    Due 11-18-16

    Description:
    The purpose of this program is to simulate the solar system. Functionality
    that was implemented was the ability to change animation speeds, zoom in and
    out, single step animation, change between wireframe and sphere drawings,
    switch between showing the texture for each planet or not, pan around the
    solar system, rotate the view around around the y and x axis and finally
    turn smooth lighting on and off. The planets drawn are the sun, moon, earth,
    mars, venus, uranus, neptune, saturn, mercury and jupiter.
*/
#include "solar.h"

using namespace std;

/*
    Name: main
    Author: Benjamin Kaiser and Taylor Doell
    Description:  This function is just the main function that the C++ language
    requires to compile and run.  It calls glutMainLoop which is really our main
    function/loop.
*/
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

/*
    Name: makeMenu
    Author: Benjamin Kaiser and Taylor Doell
    Description:  This function creates the menu that is displayed when a user
    right clicks on the screen. The menu displays the functionality of the
    programs and how to accomplish a certain task. It also performs the operation
    for the particulation menu item that is selected.
*/
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
	glutAddMenuEntry("R	 - Increase Wireframe Resolution", 7);
	glutAddMenuEntry("D  - Decrease Wireframe Resolution", 8);
    glutAddMenuEntry("Rotate Right (Right Arrow)", 9);
    glutAddMenuEntry("Rotate Left (Left Arrow)", 10);
    glutAddMenuEntry("Rotate Up (Up Arrow)", 11);
    glutAddMenuEntry("Rotate Down (Down Arrow)", 12);
    glutAddMenuEntry("Zoom In (Mouse Wheel up)", 13);
    glutAddMenuEntry("Zoom Out (Mouse Wheel down)", 14);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/*
    Name: menuSelection
    Author: Benjamin Kaiser and Taylor Doell
    Description:  This function handles the menu item seleted and calls the
    appropriate function in order to accomplish the specific task.
*/
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
			keyboard('R', 0, 0);
			break;
		case 8:
			keyboard('D', 0, 0);
			break;
        case 9:
            specialInput(GLUT_KEY_RIGHT, 0, 0);
            break;
        case 10:
            specialInput(GLUT_KEY_LEFT, 0, 0);
            break;
        case 11:
            specialInput(GLUT_KEY_UP, 0, 0);
            break;
        case 12:
            specialInput(GLUT_KEY_DOWN, 0, 0);
            break;
        case 13:
            mouse(3, GLUT_DOWN, 0, 0);
            break;
        case 14:
            mouse(4, GLUT_UP, 0, 0);
            break;
        default:
            break;
    }
}

/*
    Name: OpenGLInit
    Author: Benjamin Kaiser and Taylor Doell
    Description:  This function initializes some of the OpenGL values such as color
    and the clear color. Also sets the shade model to flat to start.
*/
void OpenGLInit()
{
    glShadeModel( GL_FLAT );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
}

/*
    Name: ResizeWindow
    Author: Code provided on the website
    Description:  This function keeps the aspect ratio of the program if the user
    happens to resize the window.
*/
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

/*
    Name: Animate
    Author: Benjamin Kaiser and Taylor Doell
    Description:  This function handles the animation and the redrawing of the
    graphics window contents. It performs a rotation to start the solar system
    at a slight angle and also sets where our view is shown by using the 'zoom'
    factor in the glTranslatef method call. That glTranslatef method call also
    specifies the x and y pan values for where the user is currently positioned.
*/
void Animate()
{
    // Clear the window
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Load new matrix identity
    glLoadIdentity();

    // Back off -100 units to be able to view from the origin.
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

/*
    Name: CollectPlanetData
    Author: Benjamin Kaiser and Taylor Doell
    Description:  This function collects all the planet data from the planetdata.info
    file. It reads in the info and then stores each planets information in an
    instance of the planet class. All that information is read in at startup and
    stored for the remainder of the program.
*/
vector<Planet> CollectPlanetData()
{
    int rows;
    int cols;
    double radius;
    double distance;
    double year;
    double day;
    string name;
    string imageFile;
    Color planetColor;
    unsigned char* data;
    vector<Planet> planets;

    ifstream fin("planetdata.info");

    // Only read in file if the file was opened correctly
    if (fin)
    {
        while (fin >> name >> radius >> distance >> year >> day >> imageFile >> planetColor.red >> planetColor.green >> planetColor.blue)
        {
            Planet planet;
            Texture texture;

            imageFile = "texture/" + imageFile;

            // Set all properties to their appropriate value from the file
            planet.setName(name);
            planet.setRadius(radius);
            planet.setDistance(distance);
            planet.setYear(year);
            planet.setDay(day);

            // Set the color of the planet
            planet.setPlanetColor(planetColor);

            // Load the texture and store it in the instance of planet
            LoadBmpFile(imageFile.c_str(), rows, cols, data);
            texture.path = imageFile;
            texture.height = rows;
            texture.width = cols;
            texture.imageDataArray = data;

            planet.setTexture(texture);

            // Add planet to vector of already read in planets
            planets.push_back(planet);
        }
    }
    else
    {
        // Output error and exit if the file did not open properly
        cout << "Unable to open planetary information.  Exiting." << endl;
        exit(1);
    }

    fin.close();

    // Load and store the texture for solars rings
    LoadBmpFile("texture/saturnringssideways.bmp", rows, cols, data);
    ringTexture.path = "texture/saturnringssideways.bmp";
    ringTexture.height = rows;
    ringTexture.width = cols;
    ringTexture.imageDataArray = data;

    return planets;
}
