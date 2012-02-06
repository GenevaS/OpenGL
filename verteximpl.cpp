/*Class: Vertex (for use with OpenGL/GLUT)
* ----------------------------------------
* Public Header: vertex.h
* Implementation: verteximpl.cpp
* ----------------------------------------
* This class contains all necessary functions that are needed to
* create and store data for mobile vertecies. It can be used in a
* program by using the following class call:
*
*				#include vertex.h
*
* Please note that this class uses the OpenGL/GLUT library and will
* not be accessible if these libraries do not exist or cannot be 
* accessed on your computer.
*/

#include <stdlib.h>
#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include "math.h"

using namespace std;

#include "vertex.h"

/* Public Functions */

/* Class Constructor and Destructor */

/* Constructor
 * -----------
 * The class constructor takes in parameters about two points, as well
 * as the point's size and colour. From the two points, the slope will
 * be used to determine the delta x and y values. From these, the correct
 * travel direction on the screen can be determined. We can also determine
 * the initial speed from the delta values.
*/

Vertex::Vertex(double x1, double y1, double x2, double y2, int size, double colour[3])
{
	bool flagx = false;
	bool flagy = false;

	//Calculating half of the screen width and height
	long fullScreenWidth = glutGet(GLUT_SCREEN_WIDTH);
	long fullScreenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	long halfWidth = fullScreenWidth / 2;
	long halfHeight = fullScreenHeight / 2;

	//Calculating relative position of points on the screen
	positionx = (x1 - halfWidth) / halfWidth;
	positiony = -1 * (y1 - halfHeight) / halfHeight;


	//Calculating the components of the slope	
	x2 = (x2 - halfWidth) / halfWidth;
	y2 = -1 * (y2 - halfHeight) / halfHeight;

	deltax = x2 - positionx;
	deltay = y2 - positiony;

	//Determining the speed of the point
	speedx = DetermineSpeed(deltax);
	speedy = DetermineSpeed(deltay);

	if (deltax < 0)
	{
		deltax = -1 * deltax;
		flagx = true;
	}
	if (deltay < 0)
	{
		deltay = -1 * deltay;
		flagy = true;
	}
	//Adjusting the delta values based on the speeds
	while (deltax > 1) deltax = deltax / 10;
	while (deltay > 1) deltay = deltay / 10;

	if (flagx == true) deltax = -1 * deltax;
	if (flagy == true) deltay = -1 * deltay;
	
	deltax = deltax * 10;
	deltay = deltay * 10;

	//Direct transfer of size and colour data
	vertexSize = size;

	vertexColour[0] = colour[0];
	vertexColour[1] = colour[1];
	vertexColour[2] = colour[2];
}

/* Destructor
 * ----------
 * The destructor allows the program to reclaim memory
 * associated with the vertex class when it is no longer
 * needed.
*/

Vertex::~Vertex()
{
	/* Empty */
}

/* Global Functions */

/*
 * Method: UpdatePosition
 * Scope: Public
 * Usage: point.UpdatePosition();
 * ------------------------------
 * This function alters the points position values such that they
 * are moving along the determined direction vector. It adds the 
 * values for delta x and delta y to the current position and then
 * overwrites the current position values with the new calculated
 * ones.
*/

void Vertex::UpdatePosition()
{
	double tempx = deltax * pow(double(10), speedx);
	double tempy = deltay * pow(double(10), speedy);

	//If the new positions are at the screen edges
	if ((positionx + tempx < -1) || (positionx + tempx > 1)) 
	{
		tempx = -1 * tempx;
		deltax = -1 * deltax;
	}

	if ((positiony + tempy < -1) || (positiony + tempy > 1))
	{
		tempy = -1 * tempy;
		deltay = -1 * deltay;
	}

	//Update positions
	positionx += tempx;
	positiony += tempy;

	return;
}

/*
 * Method: ChangeSpeed
 * Usage: vertexobject.ChangeSpeed(true/false);
 * --------------------------------------------
 * This function allows for the changing of a vertex object's
 * speed. It allows one speed faster and one speed slower than 
 * the original DetermineSpeed() function. This allows for more 
 * choice, and the user may prefer looking at snow  or an nearly
 * immobile screen rather than points.
*/

void Vertex::ChangeSpeed (bool increase) 
{
	if (increase == true)
	{
		if (speedx < -3) speedx += 1;
		if (speedy < -3) speedy += 1;
	}
	else
	{
		if (speedx > -6) speedx -= 1;
		if (speedy > -6) speedy -= 1;
	}
	
	return;
}

/*
 * Method: ChangeSize
 * Usage: vertexobject.ChangeSize(newSize);
 * ----------------------------------------
 * This function is meant to prevent the user from directly
 * accessing the Vertex object's size.
*/

void Vertex::ChangeSize (int newSize)
{
	vertexSize = newSize;

	return;
}

/*
 * Method: ChangeColour
 * Usage: vertexobject.ChangeColour(colour array of size 3);
 * ---------------------------------------------------------
 * This function is meant to prevent the user from directly
 * accessing the Vertex object's colour information.
*/

void Vertex::ChangeColour (double newColour[3]) 
{
	vertexColour[0] = newColour[0];
	vertexColour[1] = newColour[1];
	vertexColour[2] = newColour[2];

	return;
}

/* Private Functions */

/*
* Method: DetermineSpeed
* Scope: Private
* Usage: speedx/speedy = DetermineSpeed(deltax/deltay);
* -----------------------------------------------------
* This function is used to determine how fast a point moves
* across the screen. It assumes that values larger than 10^-4
* are too fast, defaulting them to 10^-4. The slowest speed
* allowed is 10^-6
* The value returned by the function is the expontent only (ie.
* -4, -5 or -6)
*/

int Vertex::DetermineSpeed(double change)
{
	int speed = 0;

	while (true)
	{
		change = change * 10;
		if (speed <= -4 || speed >= -6) break;
		speed -= 1;
	}

	if (speed > -4) speed = -4;

	else if (speed < -6) speed = -6;

	return speed;
}