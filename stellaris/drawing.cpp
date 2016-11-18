#include "drawing.h"

void DrawPlanets()
{
    int direction = -1;

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

            if (planet.getName() != "Moon")
            {
                DrawOrbitRing(planet);
                DrawStrokeString(planet.getName(), planet.getDistance(), direction * 2, 2);
                direction *= -1;
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
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
    GLUquadric* diskObject = gluNewQuadric();

    Color planetColor = planet.getPlanetColor();

    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    float planetEmission[] = {0, 0, 0, 0};
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, planetEmission );
    SetColor(planetColor.red, planetColor.green, planetColor.blue);
    // glColor3ub(255, 255, 255);
    glDisable(GL_COLOR_MATERIAL);


    glRotatef(360.0 * planet.getDayOfYear() / planet.getYear(), 0.0, 1.0, 0.0);

    glTranslatef(planet.getDistance(), 0.0, 0.0);

    glRotatef(360.0 * planet.getHourOfDay() / planet.getDay(), 0.0, 1.0, 0.0);

    DrawSphere(planet);

    if (drawRings == true)
    {
        diskObject = gluNewQuadric();
		if (isTextured == true)
		{
			glEnable(GL_TEXTURE_2D);
    		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ringTexture.width, ringTexture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, ringTexture.imageDataArray);
			gluQuadricTexture(diskObject, GL_TRUE);
		}
		else
		{
			glDisable(GL_TEXTURE_2D);
		}
		//gluDisk(diskObject, planet.getRadius() + 2, planet.getRadius() + 10, 20, 20);

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

    glEnable(GL_COLOR_MATERIAL);
    float planetEmission[] = {0, 0, 0, 0};
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, planetEmission );
    SetColor(earthColor.red, earthColor.green, earthColor.blue);
    glDisable(GL_COLOR_MATERIAL);

    DrawSphere(planet);

    glPopMatrix();
}

void DrawMoon(Planet planet)
{
    Color moonColor = planet.getPlanetColor();

    glRotatef( 360.0 * 12.0 * planet.getDayOfYear() / planet.getYear(), 0.0, 1.0, 0.0 );
    glTranslatef( planet.getDistance(), 0.0, 0.0 );

    glEnable(GL_COLOR_MATERIAL);
    float planetEmission[] = {0, 0, 0, 0};
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, planetEmission );
    SetColor(moonColor.red, moonColor.green, moonColor.blue);
    glDisable(GL_COLOR_MATERIAL);

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

void DrawOrbitRing(Planet planet)
{
    GLUquadric* diskObject = gluNewQuadric();

    glRotatef(90.0, 1.0, 0.0, 0.0);

    glEnable(GL_COLOR_MATERIAL);
    float ringEmission[] = {1, 1, 1, 0};
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, ringEmission );
    glColor3ub(255, 255, 255);
    glDisable(GL_COLOR_MATERIAL);

    gluCylinder(diskObject, planet.getDistance(), planet.getDistance() + 0.25, 0, 100, 10);

    glRotatef(-90.0, 1.0, 0.0, 0.0);
}

void SetColor(int red, int green, int blue)
{
    glEnable(GL_COLOR_MATERIAL);

    glColor3ub(red, green, blue);

    glDisable(GL_COLOR_MATERIAL);
}

void DrawStrokeString(string textToPrint, float x, float y, int fontSize)
{
    // Set font size scaling to change the size
    double fontScaling = fontSize / 100.0;
    SetColor(255, 255, 255);

    //glColor3ub(255, 255, 255); // Set text color to white
    glEnable(GL_COLOR_MATERIAL);
    float ringEmission[] = {1, 1, 1, 0};
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, ringEmission );
    glColor3ub(255, 255, 255);
    glDisable(GL_COLOR_MATERIAL);

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
