/*Class: Vertex (for use with OpenGL/GLUT)
* ----------------------------------------
* Public Header: vertex.h
* Private Header: vertexprivate.h
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

#ifndef _vertex_h
#define _vertex_h

#include <stdlib.h>
#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

/*Class: Vertex
* --------------
* This class is used to represent a vertex in an OpenGL program that is
* expected to move about the screen.
*/

class Vertex {
public:

	/* Public Class Variables */
	
	double positionx;
	double positiony;

	int vertexSize;
	double vertexColour[3];

	/*
	 * Constructor: Vertex
	 * Usage: Vertex point (x1, y1, x2, y2, size, colour[3]);
	 * -------------------------------------------------------------------------
	 * The constructor creates a new point record. The record stores information
	 * such as the current position (x, y), the slope of the vector between the
	 * current point and its chosen direction (deltax, deltay), the magnitude of
	 * its speed (speedx, speedy) as well as its size and colour.
	 * Please note that deltax and deltay will also help determine the point's
	 * speed.
	*/

	Vertex (double x1, double y1, double x2, double y2, int size, double colour[3]);

	/*
	 * Destructor: ~Vertex
	 * Usage: Usually implicit
	 * -------------------
	 * The destructor deallocates memory when the Vertex object is no longer
	 * needed. This will help with the program's memory and run times.
	 */

	~Vertex();

	/*
	 * Methods: UpdatePosition, ChangeSpeed, ChangeSize, ChangeColour
	 * Usage: point.UpdatePosition();
	 *		  point.ChangeSpeed(bool increase);
	 *        point.ChangeSize(newSpeed);
	 *		  point.ChangeColour(newColour);
	 * --------------------------------------------------------------
	 * These methods are used to alter the vertex record values.
	 * UpdatePosition does not require extra data, as the process only
	 * requires the data found within the Vertex object. ChangeSpeed 
	 * requires a boolean to tell it if the speed is being increased (True)
	 * or decreased (False). ChangeSize expects an integer arguement to tell
	 * it which point/line size is required, and ChangeColour expects a new
	 * colour array (R, G, B).
	 */

	void UpdatePosition ();
	void ChangeSpeed (bool increase);
	void ChangeSize (int newSize);
	void ChangeColour (double newColour[3]);

private:
	#include "vertexprivate.h"
};

#endif