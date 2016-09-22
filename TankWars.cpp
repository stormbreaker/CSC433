#include "TankWars.h"

#ifdef __APPLE__
	#include <GLUT/glut.h> // MacOS include
#elif __linux__
	#include <GL/glut.h> // LinuxOS include
#endif

using namespace std;

Terrain testTerrain(MAX_X);
bool IsCurrentLeft = true;
bool DidFireTank = false;
Tank RightTank(false);
Tank LeftTank(true);

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

    LeftTank.SetTankCoords(100, TerrainYValueAtX(100), true);
    RightTank.SetTankCoords(MAX_X - 100, TerrainYValueAtX(MAX_X - 100), false);

    glutMainLoop();

    return 0;
}

void display( void )
{
    vector<Coordinate> fireCoords;
    glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINE_STRIP);
        glColor3ub(84, 60, 14);

		for (Coordinate point : testTerrain.getTerrainData())
		{
			glVertex2dv(point.coordinates);
		}
	glEnd();

    glBegin(GL_LINE_LOOP);
		glColor3ub(255, 255, 255);

        for (Coordinate xyPair : LeftTank.DrawCoords)
        {
            glVertex2dv(xyPair.coordinates);
        }
    glEnd();

    glBegin(GL_LINE_LOOP);
		glColor3ub(255, 255, 255);

        for (Coordinate xyPair : RightTank.DrawCoords)
        {
            glVertex2dv(xyPair.coordinates);
        }
    glEnd();

    if (DidFireTank == true)
    {
        if (IsCurrentLeft == true)
        {
            fireCoords = LeftTank.GetFireCoords();
        }
        else
        {
            fireCoords = RightTank.GetFireCoords();
        }

        glBegin(GL_LINE_STRIP);
            for (Coordinate xyPair : fireCoords)
            {
                glVertex2dv(xyPair.coordinates);
            }
        glEnd();

        DidFireTank = false;
        IsCurrentLeft = !IsCurrentLeft;
    }

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
		// Plus key increases velocity
		case PLUS_KEY:
			ModifyTankVelocity(2.5);
			break;
		// minus key decreses velocity
		case MINUS_KEY:
			ModifyTankVelocity(-2.5);
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

void MoveFiringAngle(int direction)
{
	double angle;

	if (IsCurrentLeft)
	{
		angle = 0;
	}
	else
	{
		angle = PI;
	}

	if (direction == GLUT_KEY_UP)
	{
		if (IsCurrentLeft)
		{
			angle = FIVE_DEGREES;
		}
		else
		{
			angle = 0 - FIVE_DEGREES;
		}
	}
	else if (direction == GLUT_KEY_DOWN)
	{
		if (IsCurrentLeft)
		{
			angle = 0 - FIVE_DEGREES;
		}
		else
		{
			angle = FIVE_DEGREES;
		}
	}

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
		x = tank.velocity * timeCount * cos(tank.fireAngle);
		y = (tank.velocity * timeCount * sin(tank.fireAngle)) - (GRAVITY * pow(timeCount, 2))/2;

        xOffset = 20;
        yOffset = 10;

        if (IsCurrentLeft == false)
        {
            xOffset *= -1;
        }

        x += tank.CenterCoords[X_COORD] + xOffset;
        y += tank.CenterCoords[Y_COORD] + yOffset;

        tempCoord.coordinates[X_COORD] = x;
		tempCoord.coordinates[Y_COORD] = y;

        if (FindMountainCollision(x, y) == false &&
            FindTankCollision(x, y) == false)
        {
            projectilePath.push_back(tempCoord);
        }
        else
        {
            break;
        }
	}

    tank.SetFireCoords(projectilePath);
}

bool FindMountainCollision(double x, double y)
{
    double yValueAtX = 0;
    bool foundCollision = false;

    yValueAtX = TerrainYValueAtX(x);

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

    if (abs(xDiff) < 20 && abs(yDiff) < 10)
    {
        cout << "Collision" << endl;

        foundCollision = true;
    }

    return foundCollision;
}

void SetTankPosition(Tank &tank, double xCoord)
{
    xCoord += tank.CenterCoords[X_COORD];

    tank.SetTankCoords(xCoord, TerrainYValueAtX(xCoord), IsCurrentLeft);

    if (xCoord < 0)
    {
        tank.SetTankCoords(0, TerrainYValueAtX(0), IsCurrentLeft);
    }
    else if (xCoord > MAX_X)
    {
        tank.SetTankCoords(MAX_X, TerrainYValueAtX(MAX_X), IsCurrentLeft);
    }
}

void SetFireAngle(Tank &tank, double angle)
{
	angle += tank.fireAngle;

	tank.fireAngle = angle;

	if (angle > PI)
	{
		tank.fireAngle = PI;
	}
	else if (angle < 0)
	{
		tank.fireAngle = 0;
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

void ModifyTankVelocity(double velocityChange)
{
    if (IsCurrentLeft == true)
    {
        LeftTank.velocity += velocityChange;
    }
    else
    {
        RightTank.velocity += velocityChange;
    }
}

double TerrainYValueAtX(double xValue)
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
