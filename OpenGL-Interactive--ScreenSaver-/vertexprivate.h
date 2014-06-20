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
* The variables and functions found in this header should not be
* directly accessible to the user. They are used by the other 
* functions of this class.
*/

double deltax;
double deltay;

double speedx;
double speedy;

int DetermineSpeed(double change);