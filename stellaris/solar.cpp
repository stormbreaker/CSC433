#include "solar.h"

using namespace std;


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

    int rows;
    int cols;

    unsigned char* data;

    vector<Planet> planets;

    ifstream fin("planetdata.info");

    if (fin)
    {
        while (fin >> name >> radius >> distance >> year >> day >> imageFile >> planetColor.red >> planetColor.green >> planetColor.blue)
        {
            Planet planet;
            Texture texture;

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

    LoadBmpFile("texture/saturnringssideways.bmp", rows, cols, data);
    ringTexture.path = "texture/saturnringssideways.bmp";
    ringTexture.height = rows;
    ringTexture.width = cols;
    ringTexture.imageDataArray = data;

    return planets;
}
