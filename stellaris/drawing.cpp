#include "drawing.h"

/*
    Name: DrawPlanets
    Author: Benjamin Kaiser and Taylor Doell
    Description:  This function is the main drawing function of the entire program.
    It loops through a vector that contains all of the planets and then calls
    the different functions.  It checks for special cases such as earth moon and
    sun and calls the special functions for those if necessary.  This function also
    handles animation for incrementing values such as HourOfDay and DayOfYear for
    the different planets.  This function also calls the drawing methods for the
    orbital path values and the labels.
*/
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

            // draw labels for everything but moon
            if (planet.getName() != "Moon")
            {
                DrawOrbitRing(planet);
                DrawStrokeString(planet.getName(), planet.getDistance(), direction * 2, 2);
                direction *= -1;
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
            }
            // earth and moon are special cases since the moon depends on the earth
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

            // Saturn is special cased because of the rings
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

/*
    Name: DrawPlanet
    Author: Benjamin Kaiser and Taylor Doell
    Description:  This function is the generic draw planet function and it takes
    an instance of the planet class as well as whether or not this planet has
    rings.  The material properties for this planet are set and if rings are drawn,
    the properties for that are set as well.
*/
void DrawPlanet(Planet planet, bool drawRings)
{
    GLUquadric* diskObject = gluNewQuadric();

    Color planetColor = planet.getPlanetColor();

    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    float planetEmission[] = {0, 0, 0, 0};
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, planetEmission );
    SetColor(planetColor.red, planetColor.green, planetColor.blue);
    glDisable(GL_COLOR_MATERIAL);

    //orbit
    glRotatef(360.0 * planet.getDayOfYear() / planet.getYear(), 0.0, 1.0, 0.0);

    glTranslatef(planet.getDistance(), 0.0, 0.0);

    // daily rotation
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

        gluCylinder(diskObject, planet.getRadius() + 10, planet.getRadius() + 2, 0, 20, 20);
    }

    glPopMatrix();
}

/*
    Name: DrawSun
    Author: Taylor Doell and Benjamin Kaiser
    Description:  This function is the special case drawing function for the sun.
    It takes a planet instance and sets all of the lighting properties for the
    solar system.  It sets the sun to emit a yello color and it also does not
    allow the sun to spin.  The reason the sun is not allowed to spin is
    because if it were, it was spinning super fast and was ugly looking.
*/
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

/*
    Name: DrawEarth
    Author: Benjamin Kaiser and Taylor Doell
    Description:  This function is the special case function for drawing the earth
    It also sets the material properties and then draws the sphere.  Earth
    and moon ahd to be special cases in order to get the moon to rotate about the
    earth.
*/
void DrawEarth(Planet planet)
{
    Color earthColor = planet.getPlanetColor();

    // orbit
    glRotatef( 360.0 * planet.getDayOfYear() / planet.getYear(), 0.0, 1.0, 0.0 );
    glTranslatef( planet.getDistance(), 0.0, 0.0 );
    glPushMatrix();

    // rotation on axis
    glRotatef( 360.0 * planet.getHourOfDay() / planet.getDay(), 0.0, 1.0, 0.0 );

    glEnable(GL_COLOR_MATERIAL);
    float planetEmission[] = {0, 0, 0, 0};
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, planetEmission );
    SetColor(earthColor.red, earthColor.green, earthColor.blue);
    glDisable(GL_COLOR_MATERIAL);

    DrawSphere(planet);

    glPopMatrix();
}

/*
    Name: DrawMoon
    Author: Benjamin Kaiser and Taylor Doell
    Description:  This function is the special case function for the moon.  This
    had to be a special function and it has to be called immediately after
    drawing the earth because it does not push on or pop another matrix that would
    cause it to work as another planet.
*/
void DrawMoon(Planet planet)
{
    Color moonColor = planet.getPlanetColor();

    // orbit the earth
    glRotatef( 360.0 * 12.0 * planet.getDayOfYear() / planet.getYear(), 0.0, 1.0, 0.0 );
    glTranslatef( planet.getDistance(), 0.0, 0.0 );

    // rotate on axis
    glRotatef( 360.0 * planet.getHourOfDay() / planet.getDay(), 0.0, 1.0, 0.0 );


    glEnable(GL_COLOR_MATERIAL);
    float planetEmission[] = {0, 0, 0, 0};
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, planetEmission );
    SetColor(moonColor.red, moonColor.green, moonColor.blue);
    glDisable(GL_COLOR_MATERIAL);

    DrawSphere(planet);
}

/*
    Name: DrawSphere
    Author: Benjamin Kaiser and Taylor Doell
    Description:  This function is the generalized function for drawing all of
    the planets.  It checks to see if the global flags for textured, and solid vs
    wireframe spheres are set.  If they are, then they draw things appropriately
*/
void DrawSphere(Planet planet)
{
    GLUquadric* ball = gluNewQuadric();

    // flip into upright position so axis of planet faces upwards
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

/*
    Name: DrawOrbitRing
    Author: Benjamin Kaiser and Taylor Doell
    Description:  This function draws the orbital path rings of each of the planets.
    Material properties had to be set here to make the text not be affected by the
    lighting.
*/
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

/*
    Name: SetColor
    Author: Benjamin Kaiser and Taylor Doell
    Description:  This function is a helper function for the drawing functions
    and setting material properties.  It takes 3 ints that make up and RGB
    and then sets the current GL draw color to those values.
*/
void SetColor(int red, int green, int blue)
{
    glEnable(GL_COLOR_MATERIAL);

    glColor3ub(red, green, blue);

    glDisable(GL_COLOR_MATERIAL);
}

/*
    Name: DrawStrokeString
    Author: Benjamin Kaiser and Taylor Doell
    Description:  This function draws text for the planetary orbital labels.
    It is pretty well inline commented but there are some material properties
    that need to be set here as well so that the lighting model does not affect
    them similar to the orbital ring patterns.  
*/
void DrawStrokeString(string textToPrint, float x, float y, int fontSize)
{
    // Set font size scaling to change the size
    double fontScaling = fontSize / 100.0;
    SetColor(255, 255, 255);

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
