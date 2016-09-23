#include "TankWars.h"

#ifdef __APPLE__
	#include <GLUT/glut.h> // MacOS include
#elif __linux__
	#include <GL/glut.h> // LinuxOS include
#endif

/*
	CSC 433 - Computer Graphics
	Dr. John Weiss
	Programming Assignment #1 - Tank Wars
	Benjamin Kaiser and Taylor Doell
	Due 9-22-16

	Description:
	This program is a simple introduction into computer graphics and OpenGL.  The
	purpose of the program is to build a simple arcade game between two tanks which
	will fire at each other over the top of a mountain. The first player to hit
	the other tank wins the game.  When this happens, the screen displays the word
	"Win!" above the tank which won and allows the option to hit R to replay the
	game with a new terrain.  The tank's movement across the screen is controlled
	by the left/right arrow keys.  The tank's firing angle is controlled by the up/down
	arrow keys.  The tank's firing velocity is controlled by the +/- keys.  The
	tank fires by pressing the space key.  The tank turns switch automatically.
*/

using namespace std;

// Global variables for Game
bool IsCurrentLeft = true;
bool DidFireTank = false;
bool GameOver = false;
Terrain testTerrain(MAX_X); // Terrain class to generate the terrain
Tank LeftTank(true);        // Initialize left tank
Tank RightTank(false);      // Initialize right tank

int main(int argc, char *argv[])
{
    // Setup glut window and callback methods
    glutInit(&argc, argv);         // initialize GLUT
    glutCreateWindow("Tank Wars"); // open window and specify title
    glutDisplayFunc(display);	   // display callback: how to redisplay window
	glutReshapeFunc(reshape);      // Reshaping function - Snaps window back to start
    glutKeyboardFunc(keyboard);    // Initialize both keyboard methods
    glutSpecialFunc(specialKeyboard);
    glutReshapeWindow(ScreenWidth, ScreenHeight); // Set screen width and height

    // Set the initial state of the game
    ResetGame();

    // Enter glut main loop
    glutMainLoop();

    return 0;
}

void display( void )
{
    vector<Coordinate> fireCoords;
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw string at coordinate
    DrawStrokeString(FormatMenu(), 20, MAX_Y - 40, 15);

    // Draw the terrain onto the screen
	glBegin(GL_LINE_STRIP);
        for (Coordinate point : testTerrain.getTerrainData())
		{
            // Change colors of terrain depending on elevation
            if (point.coordinates[Y_COORD] < 350)
            {
                // Draw green for lower elevation
                glColor3ub(51, 153, 51);
            }
            else if (point.coordinates[Y_COORD] < 500)
            {
                // Draw middle elevation brown
                glColor3ub(84, 60, 14);
            }
            else
            {
                // Draw a beautiful snow capped peak
                glColor3ub(140, 140, 140);
            }

            // Give coordinate to gl to draw
			glVertex2dv(point.coordinates);
		}
	glEnd();

    // Draw left tank on screen
    glBegin(GL_LINE_LOOP);
        // Color left tank blue
		glColor3ub(0, 102, 255);

        // Give coordinates to gl to draw
        for (Coordinate xyPair : LeftTank.DrawCoords)
        {
            glVertex2dv(xyPair.coordinates);
        }
    glEnd();

    // Draw right tank on screen
    glBegin(GL_LINE_LOOP);
        // Color left tank orange
		glColor3ub(255, 102, 0);

        // Give coordinates to gl to draw
        for (Coordinate xyPair : RightTank.DrawCoords)
        {
            glVertex2dv(xyPair.coordinates);
        }
    glEnd();

    // If a tank was fired, draw firepath on the screen
    if (DidFireTank == true)
    {
        // Pick which tank was shot and get the firepath coordinates
        if (IsCurrentLeft == true)
        {
            // Set Color for path to blue
            glColor3ub(0, 102, 255);
            fireCoords = LeftTank.GetFireCoords();
        }
        else
        {
            // Set Color for path to orange
            glColor3ub(255, 102, 0);
            fireCoords = RightTank.GetFireCoords();
        }

        // Loop and give coordinates to gl to draw
        glBegin(GL_LINE_STRIP);
            for (Coordinate xyPair : fireCoords)
            {
                glVertex2dv(xyPair.coordinates);
            }
        glEnd();

        // Set DidFireTank to false
        DidFireTank = false;

        // If the game is over, GameOver is set in tank collision method
        if (GameOver == true)
        {
            // Check which tank to display win over
            if (IsCurrentLeft == true)
            {
                // Display win above the tank
                DrawStrokeString("WIN!", LeftTank.CenterCoords[X_COORD] - 40,
                                         LeftTank.CenterCoords[Y_COORD] + 50, 40);
            }
            else
            {
                // Display win above the tank
                DrawStrokeString("WIN!", RightTank.CenterCoords[X_COORD] - 40,
                                         RightTank.CenterCoords[Y_COORD] + 50, 40);
            }
        }
        else
        {
            // Switch tanks if the game if no one has won
            IsCurrentLeft = !IsCurrentLeft;
        }
    }

    // Draw text for the tanks information such as Velocity, angle and position
    DrawStrokeString(FormatTankInfoString(LeftTank, RightTank), 475, 100, 17);

    // Flush all graphics to the screen
    glFlush();
}

void reshape(int width, int height)
{
    // Call methods to refresh the screen
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set max x and y for the screen
    SetMaxXY(ScreenWidth, ScreenHeight);

    // Set 2D coordinates
    gluOrtho2D(0, MAX_X, 0, MAX_Y);

    // Snap window back to original size and set viewport to the width and height
    glutReshapeWindow(ScreenWidth, ScreenHeight);
    glViewport(0, 0, ScreenWidth, ScreenHeight);
}

void keyboard(unsigned char key, int x, int y)
{
    // Only allow escape key and r key if the game is over
    if (GameOver == false || key == ESC_KEY || key == R_KEY)
    {
        // process keypresses
        switch(key)
        {
            case SPACE_KEY:
                // Fire weapon
    			if (IsCurrentLeft)
    			{
    				SetFireCoordinates(LeftTank);
    			}
    			else if (!IsCurrentLeft)
    			{
    				SetFireCoordinates(RightTank);
    			}

                DidFireTank = true;

                glutPostRedisplay();
                break;
            // Escape key quits program
            case ESC_KEY:
                exit(0);
                break;
    		// Plus key increases Velocity
    		case PLUS_KEY:
    			ModifyTankVelocity(2.5);
                glutPostRedisplay();
    			break;
    		// minus key decreses Velocity
    		case MINUS_KEY:
    			ModifyTankVelocity(-2.5);
                glutPostRedisplay();
    			break;
            case LOWER_R_KEY:
            case R_KEY:
                ResetGame();
                glutPostRedisplay();
                break;

            // anything else redraws window
            default:
                glutPostRedisplay();
                break;
        }
    }
}

void specialKeyboard(int key, int x, int y)
{
    if (GameOver == false)
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
                // raise tank barrel
    			MoveFiringAngle(GLUT_KEY_UP);
                glutPostRedisplay();
                break;
            case GLUT_KEY_DOWN:
                // lower tank barrel
    			MoveFiringAngle(GLUT_KEY_DOWN);
                glutPostRedisplay();
                break;

            // anything else redraws window
            default:
            glutPostRedisplay();
                break;
        }
    }
}

void ResetGame()
{
    // Create new tanks
    LeftTank = Tank(true);
    RightTank = Tank(false);

    // Reset the booleans to recreate starting the game
    GameOver = false;
    IsCurrentLeft = true;

    // Set MaxXY for terrain generation and coordinate scaling
    SetMaxXY(ScreenWidth, ScreenHeight);

    // Create new Terrain class
    testTerrain = Terrain(MAX_X);

    // Set initial tank positions
    LeftTank.SetTankCoords(100, TerrainYValueAtX(100), true);
    RightTank.SetTankCoords(MAX_X - 100, TerrainYValueAtX(MAX_X - 100), false);
}

void MoveTank(int direction)
{
    // Variable declaration
    double xCoord = 0;

    // Use 10 or -10 depending on key pressed
    if (direction == GLUT_KEY_RIGHT)
    {
        xCoord = 10;
    }
    else if (direction == GLUT_KEY_LEFT)
    {
        xCoord = -10;
    }

    // Set the correct tanks position according to current tank
    if (IsCurrentLeft == true)
    {
        SetTankPosition(LeftTank, xCoord);
    }
    else
    {
        SetTankPosition(RightTank, xCoord);
    }

    // Display the tanks
    glutPostRedisplay();
}

void MoveFiringAngle(int direction)
{
	double angle;

    // Set initial angles in case of going below 0 or 180
	if (IsCurrentLeft == true)
	{
		angle = 0;
	}
	else
	{
		angle = PI;
	}

    // Increase angle depending on which tank is playing
	if (direction == GLUT_KEY_UP)
	{
		if (IsCurrentLeft)
		{
			angle = ANGLE_OFFSET;
		}
		else
		{
			angle = 0 - ANGLE_OFFSET;
		}
	}
    // Decrease angle depending on which tank is playing
	else if (direction == GLUT_KEY_DOWN)
	{
		if (IsCurrentLeft)
		{
			angle = 0 - ANGLE_OFFSET;
		}
		else
		{
			angle = ANGLE_OFFSET;
		}
	}

    // Set the appropriate tanks coords
	if (IsCurrentLeft)
	{
		SetFireAngle(LeftTank, angle);
	}
	else
	{
		SetFireAngle(RightTank, angle);
	}
}

void SetFireCoordinates(Tank &tank)
{
    double x;
	double y;
    double xOffset = 0;
    double yOffset = 0;
    Coordinate tempCoord;
    vector<Coordinate> projectilePath;

    for (double timeCount = 0; timeCount < 40; timeCount += .05)
	{
        // Calculate the x and y for next point in the arc
		x = tank.Velocity * timeCount * cos(tank.FireAngle);
		y = (tank.Velocity * timeCount * sin(tank.FireAngle)) - (GRAVITY * pow(timeCount, 2))/2;

        // Set offsets to line the path with the tank barrel
        xOffset = 21;
        yOffset = 13;

        // Multiply xOffset by -1 if the current tank is the Right Tank
        if (IsCurrentLeft == false)
        {
            xOffset *= -1;
        }

        // Line up the curve with the tank
        x += tank.CenterCoords[X_COORD] + xOffset;
        y += tank.CenterCoords[Y_COORD] + yOffset;

        // Check for collisions
        if (FindMountainCollision(x, y) == false &&
            FindTankCollision(x, y) == false)
        {
            // If no collisions, set coordinates
            tempCoord.coordinates[X_COORD] = x;
    		tempCoord.coordinates[Y_COORD] = y;

            // Add coordinates path of projectile
            projectilePath.push_back(tempCoord);
        }
        else
        {
            // If collision, quit loop for setting projectile path
            break;
        }
	}

    tank.SetFireCoords(projectilePath);
}

bool FindMountainCollision(double x, double y)
{
    double yValueAtX = 0;
    bool foundCollision = false;

    // Get y value of terrain at the x coordinate
    yValueAtX = TerrainYValueAtX(x);

    // If terrain y value is greater than current y, Mountain hit!
    if (yValueAtX > y)
    {
        foundCollision = true;
    }

    return foundCollision;
}

bool FindTankCollision(double x, double y)
{
    bool foundCollision = false;
    double xDiff = 0;
    double yDiff = 0;

    // Get x and y diff to see how close the projectile is
    if (IsCurrentLeft == true)
    {
        xDiff = RightTank.CenterCoords[X_COORD] - x;
        yDiff = RightTank.CenterCoords[Y_COORD] - y;
    }
    else
    {
        xDiff = LeftTank.CenterCoords[X_COORD] - x;
        yDiff = LeftTank.CenterCoords[Y_COORD] - y;
    }

    // Absolute value differences to be able to check either tank for collisions
    if (abs(xDiff) < 20 && abs(yDiff) < 10)
    {
        // Set found collision and GameOver to true
        foundCollision = true;
        GameOver = true;
    }

    return foundCollision;
}

double TerrainYValueAtX(double xValue)
{
    double y = 0;
    double m = 0;
    double x = 0;
    double b = 0;
    double yCoord = 0;
    Coordinate firstPoint;

    // Loop through terrain coordinates to get y value
    for (Coordinate coords : testTerrain.getTerrainData())
    {
        // Check to see if the X_COORD is > xValue to make sure we have a line segment
        if (coords.coordinates[X_COORD] > xValue)
        {
            // Get x y points for second point
            x = coords.coordinates[X_COORD];
            y = coords.coordinates[Y_COORD];

            // Compute the slope of the line between the points
            m = coords.coordinates[Y_COORD] - firstPoint.coordinates[Y_COORD];
            m /= coords.coordinates[X_COORD] - firstPoint.coordinates[X_COORD];

            // Compute the y intercept
            b = y - m * x;

            // Compute the equation of a line to get specific y coordinate
            yCoord = m * xValue + b + 10.0;
            break;
        }

        // Set the beginning of line segment for once we find the second point
        firstPoint = coords;
    }

    return yCoord;
}

void SetTankPosition(Tank &tank, double xCoord)
{
    // Get initial middle of the screen to prevent going over mountain
    double cutoff = (MAX_X / 2);
    xCoord += tank.CenterCoords[X_COORD]; // Offset the xCoord with tank position

    // Set tank coords
    tank.SetTankCoords(xCoord, TerrainYValueAtX(xCoord), IsCurrentLeft);

    // Determine if the tank needs to be reset to a specific point
    // If tank moves out of the screen on the left
    if (xCoord < 0)
    {
        tank.SetTankCoords(0, TerrainYValueAtX(0), IsCurrentLeft);
    }
    // If left tank tries to get to close to the peak, move back
    else if (IsCurrentLeft == true && xCoord > cutoff - 150)
    {
        cutoff -= 150;

        tank.SetTankCoords(cutoff, TerrainYValueAtX(cutoff), IsCurrentLeft);
    }
    // If right tank tries to get to close to the peak, move back
    else if (IsCurrentLeft == false && xCoord < cutoff + 150)
    {
        cutoff += 150;

        tank.SetTankCoords(cutoff, TerrainYValueAtX(cutoff), IsCurrentLeft);
    }
    // If tank moves out of the screen on the right
    else if (xCoord > MAX_X)
    {
        tank.SetTankCoords(MAX_X, TerrainYValueAtX(MAX_X), IsCurrentLeft);
    }
}

/*
	Name: SetFireAngle
	Author: Taylor Doell
	Description:  This function modifies the tanks fire angle. It determines
    if the angle is below 0 or PI radians so the tanks don't fire below 0 degrees
    and changes the angle appropriately.
*/
void SetFireAngle(Tank &tank, double angle)
{
    // Increment angle according to existing tank angle
	angle += tank.FireAngle;

    // Set tank angle to new angle
	tank.FireAngle = angle;

    // Check tank angle to determine if it is aiming below 0 degrees
	if (angle > PI)
	{
		tank.FireAngle = PI;
	}
	else if (angle < 0)
	{
		tank.FireAngle = 0;
	}
}

/*
	Name: SetMaxXY
	Author: Taylor Doell
	Description:  This function calculates the MAX_X and the MAX_Y which allows
    for keeping the same aspect ratio when changing the size of the window. The
    program always snaps back to the same size as the original screen though.
*/
void SetMaxXY(int width, int height)
{
    // Set max x and y to keep the aspect ratio
    // Set different depending on how screen is set up
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

/*
	Name: ModifyTankVelocity
	Author: Taylor Doell
	Description:  This modifies the velocity on the tank that is currently
    playing the game.
*/
void ModifyTankVelocity(double velocityChange)
{
    // Increase tank velocity depending on current tank
    if (IsCurrentLeft == true)
    {
        LeftTank.Velocity += velocityChange;
    }
    else
    {
        RightTank.Velocity += velocityChange;
    }
}

/*
	Name: FormatTankInfoString
	Author: Taylor Doell
	Description:  This is the main function for formatting the string correctly
    to show all the information regarding current tank playing, coordinates of
    the tanks, the velocity and the angle at which the tanks are pointed. It
    goes through and formats the property headers, but it calls other functions
    to format the actual numbers and values.
*/
string FormatTankInfoString(Tank leftTank, Tank rightTank)
{
    string formattedString;

    // Set *'s around the current tank
    if (IsCurrentLeft == true)
    {
        formattedString =  "         *Left Tank*         Right Tank";
    }
    else
    {
        formattedString =  "          Left Tank         *Right Tank*";
    }

    // Set string according to the current positions of the tanks
    formattedString += "\nPosition:    ";
    formattedString += FormatTankCoords(LeftTank);
    formattedString += "      ";
    formattedString += FormatTankCoords(RightTank);
    formattedString += "\nVelocity:     ";
    formattedString += FormatTankVelocity(LeftTank);
    formattedString += "        ";
    formattedString += FormatTankVelocity(RightTank);
    formattedString += "\nAngle:      ";
    formattedString += FormatTankAngle(LeftTank, true);
    formattedString += "         ";
    formattedString += FormatTankAngle(RightTank, false);

    return formattedString;
}

/*
	Name: FormatTankCoords
	Author: Taylor Doell
	Description:  This function formats the string to print for tank coordinates.
    It formats the string in the format a number with ( xValue, yValue ).
*/
string FormatTankCoords(Tank tank)
{
    string coords;
    char coord[20];

    // Format tank coords in format ( x, y )
    coords = "( ";
    sprintf(coord, "%d", (int)tank.CenterCoords[X_COORD]);
    coords += coord;
    coords += ", ";
    sprintf(coord, "%d", (int)tank.CenterCoords[Y_COORD]);
    coords += coord;
    coords += " )";

    return coords;
}

/*
	Name: FormatTankVelocity
	Author: Taylor Doell
	Description:  This function formats the string to print for tank velocity.
    It formats the string in the format a number with 1 number after the decimal
    point and then m/sec.
*/
string FormatTankVelocity(Tank tank)
{
    string coords;
    char coord[10];

    // Format tank velocity in format 3.0m/sec
    sprintf(coord, "%.1f", tank.Velocity);
    coords += coord;
    coords += "m/sec";

    return coords;
}

/*
	Name: FormatTankAngle
	Author: Taylor Doell
	Description:  This function formats the string to print for the angle of a
    tank. It converts the radians to degrees to allow the users to easily see the
    angle. It formats the string with a digit and degrees after the number.
*/
string FormatTankAngle(Tank tank, bool isLeftTank)
{
    string coords;
    double angleDegrees;
    char coord[10];

    // Get angle degrees so user can see angles easier
    angleDegrees = RadiansToDegrees(tank.FireAngle);

    // Get appropriate angle for right tank
    if (isLeftTank == false)
    {
        angleDegrees = 180.0 - angleDegrees;
    }

    // Format tank angle in format 45 degrees
    sprintf(coord, "%d", (int)angleDegrees);
    coords += coord;
    coords += " degrees";

    return coords;
}

/*
	Name: FormatMenu
	Author: Taylor Doell
	Description:  This function formats the string to print for the menu. It
    formats the string different depending on if the game is over or not. If the
    game is over, it only prints out how to close the game or restart the game.
    If the game is not over, it formats the string to show all the ways to
    interact with the game.
*/
string FormatMenu()
{
    string menuString = "";

    // Generate the ESC and R keys for closing and resetting game
    menuString = "Game Controls :";
    menuString += "\nESC - Close Game";
    menuString += "\nR - Restart Game";

    // If the game isn't over, show all the other commands to use
    if (GameOver == false)
    {
        menuString += "\nSpace - Fire Tank";
        menuString += "\n+ - Increase Velocity";
        menuString += "\n- - Decrease Velocity";
        menuString += "\nArrow Up - Increase Angle";
        menuString += "\nArrow Down - Decrease Angle";
        menuString += "\nArrow Right - Move Tank Right";
        menuString += "\nArrow Left - Move Tank Left";
    }

    return menuString;
}

/*
	Name: DrawStrokeString
	Author: Taylor Doell
	Description:  This function takes in the string to print, the x and y coordiante,
    and the fontsize to display the font in. The fontsize is used to scale the
    screen to change the size of the characters. It changes the matrix mode to a
    GL_MODELVIEW for using the push and pop matrix functions. To display new lines
    you must pop the current matrix, change the x and y coordinates and push a new
    matrix. Due to using Glut rather than FreeGlut, we must use glutStrokeCharacter
    and loop through each character in the string. Once done, we must pop the final
    matrix to the screen.
*/
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
