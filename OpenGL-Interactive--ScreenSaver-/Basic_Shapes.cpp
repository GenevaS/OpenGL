/*
 * Library: Basic Shapes
 * ---------------------
 * This library is for use by the Interactive Screen Saver program. It
 * has functions that will allow for the drawing of points, lines and
 * some basic shapes.
 * There are two point functions. One is made to handle Vertex objects,
 * and the other is to handle points declared with unpackaged (x, y)
 * co-ordinates. This library can be accessed by calling
 *
 *			#include "Basic_Shapes.h"
 *
*/

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>

#include <GL/glut.h>
#include <GL/gl.h>

#include "Basic_Shapes.h"
#include "vertex.h"

using namespace std;

/*	 Public Functions	*/

/*
 * Method: drawPoint
 * Usage: drawPoint(vertex_object);
 * --------------------------------
 * This function takes in a Vertex object and draws
 * a dot using the fields found in the object's
 * record.
*/

void drawPoint(Vertex point)
{
	glPointSize(point.vertexSize);

	glBegin(GL_POINTS);

		glColor3dv(point.vertexColour);		
		glVertex2d(point.positionx, point.positiony);

	glEnd();

	return;
}

/*
 * Method: drawStart
 * Usage: drawStart(x, y, size, c);
 * --------------------------------
 * This function operates the same way as drawPoint, except
 * it requires explicit (x, y) co-ordinates, as well as a 
 * size and colour vector.
 * It was named drawStart because it is used to draw points
 * before they have all the required data to be turned into
 * a Vertex object.
*/

void drawStart(double x, double y, int size, double colour[3])
{
	//Scaling the x and y values so that they are within the
	//co-ordinate system
	double fullScreenWidth = glutGet(GLUT_SCREEN_WIDTH);
	double fullScreenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	double halfWidth = fullScreenWidth / 2;
	double halfHeight = fullScreenHeight / 2;

	x = (x - halfWidth) / halfWidth;
	y = -1 * (y - halfHeight) / halfHeight;
	
	//Drawing the object
	glPointSize(size);

	glBegin(GL_POINTS);

		glColor3dv(colour);
		glVertex2d(x, y);

	glEnd();

	return;
}

/*
 * Method: drawLine
 * Usage: drawLine(point1, colour1, point2, colour2);
 * --------------------------------------------------
 * This function takes in co-ordinates for two points
 * as well as a vector for two colours and creates
 * a line using this data.
*/

void drawLine(double p1[2], double c1[3], double p2[2], double c2[3])
{
	glBegin(GL_LINES);
	
		glColor3dv(c1);
		glVertex2dv(p1);
	
		glColor3dv(c2);
		glVertex2dv(p2);
	
	glEnd();

	return;	
}

void drawVertexLine(Vertex point1, Vertex point2)
{
	glLineWidth(point1.vertexSize);	

	glBegin(GL_LINES);

		glColor3dv(point1.vertexColour);
		glVertex2d(point1.positionx, point1.positiony);

		glColor3dv(point2.vertexColour);
		glVertex2d(point2.positionx, point2.positiony);

	glEnd();
	return;
}

/*
 * Method: drawQuad
 * Usage: drawQuad(p1, p2, p3, p4, colour);
 * ----------------------------------------
 * This function takes in co-ordinates for four points and a single
 * colour and draws a four sided figure. It calls on the drawLine
 * function in order to draw its shape.
*/

void drawQuad(double p1[2], double p2[2], double p3[2], double p4[2], double c[3])
{
	drawLine(p1, c, p2, c);
	drawLine(p2, c, p4, c);
	drawLine(p4, c, p3, c);
	drawLine(p3, c, p1, c);

	return;
}

/*
 * Method: drawRectangle
 * Usage: drawRectangle(centre, width, height, colour);
 * ----------------------------------------------------
 * This function draws a rectangle using a centre point, height
 * and width. It calculates the relative position of the points
 * by adding or substracting half of the height to the y values
 * and half of the width to the x values.
 * Once it has the new points, it calls drawQuad to draw the 
 * shape to the screen.
*/

void drawRectangle(double c[2], double w, double h, double colour[3])
{
	long halfWidth = w / 2;
	long halfHeight = h / 2;

	double p1[2] = {c[0] + halfWidth, c[1] + halfHeight};
	double p2[2] = {c[0] - halfWidth, c[1] + halfHeight};
	double p3[2] = {c[0] + halfWidth, c[1] - halfHeight};
	double p4[2] = {c[0] - halfWidth, c[1] - halfHeight};
	
	drawQuad(p1, p2, p3, p4, colour);

	return;
}

/*
 * Method: drawCircle
 * Usage: drawCircle(centre, radius, colour);
 * ------------------------------------------
 * This function draws a smooth circle centred around <centre> and
 * with a radius <radius>. It uses the mathematical relations:
 *		x = centre + radius * cos(theta)
 *		y = centre + radius * sin(theta)
 * to calculate the relative (x, y) co-ordinates. The number of 
 * co-ordinates calculated is MAX_POINTS. MAX_POINTS must be an 
 * even number, as the drawLine function is called for every two 
 * points.
 * A higher MAX_POINTS value will result in a smoother circle.
*/

void drawCircle(double c[2], double r, double colour[3])
{
	//Constant values
	const int MAX_POINTS = 100;
	const double TWO_PI = 6.283185307;

	//Angle between each point
	long double step =  TWO_PI / MAX_POINTS;

	double p1[2];
	double p2[2];

	//Initial point
	p1[0] = c[0] + r * cos(step);
	p1[1] = c[1] + r * sin(step);

	//Subsequent points
	for (int i = 2; i <= MAX_POINTS; i++)
	{
		//Calculate second point on the line
		p2[0] = c[0] + r * cos(i * step);
		p2[1] = c[1] + r * sin(i * step);

		drawLine(p1, colour, p2, colour);

		//Shift the second point to the first point
		p1[0] = p2[0];
		p1[1] = p2[1];
	}

	//Last point - same as the initial point
	p2[0] = c[0] + r * cos(step);
	p2[1] = c[1] + r * sin(step);

	drawLine(p1, colour, p2, colour);

	return;
}

void drawFilledPolygon(vector <Vertex> corners)
{
	glBegin(GL_POLYGON);

		for (int i = 0; i < corners.size(); i++)
		{
			glColor3dv(corners[i].vertexColour);
			glVertex2d(corners[i].positionx, corners[i].positiony);
		}

	glEnd();

	return;
}