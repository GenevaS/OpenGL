/*
 * Geneva Smith
 * October 12, 2011
 * ----------------------------------------
 * This program uses the OpenGL/GLUT library to create an interactive
 * "screen saver" that manipulates a set of points. The individual point
 * data is stored in a record defined by a class called Vertex. This
 * class has been designed from scratch. Once the point data has been
 * used to create a new vertex object, it is added to the end of a vector
 * array.
 * All neccesary functionality concerning each point (eg. movement, 
 * changing the colour, etc.) has been implemented in the Vertex class.
*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <ctime>

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

//Programmer defined libraries and classes
#include "Basic_Shapes.h"
#include "vertex.h"

using namespace std;	//Allows the use of vectors and I/O

//Enumerated tyoe for modes
enum Mode {Dot, Line, Polygon, Star};
enum Channel {R, G, B};

//Default mode
Mode current = Dot;

//Vector to store all points
vector <Vertex> points;

//Stores the index of the point from <points> that marks
//the end of a polygon set
vector <int> polygonMarkers;
int lastMarker = 0;
vector <Vertex> polySet;

//Temporary values used to create the Vertex objects
double px1, px2, py1, py2;
double c[3] = {1, 1, 1};
int size = 3;
GLint lastColour = 8;

//Booleans to determine which state the program is in
bool flag1 = false;
bool randomflag = true;
bool pauseflag = false;
int limit;

int widthRange = glutGet(GLUT_SCREEN_WIDTH);
int heightRange = glutGet(GLUT_SCREEN_HEIGHT);

/*
 * Function: display
 * Usage: glutDisplayFunc(display);
 * --------------------------------
 * This function is defined by the programmer for use with the  
 * GLUT library. It is used to handle all drawing operations.
*/

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//Drawing and updating each vertex object in <points>
	if (flag1 == true)			//First point selected, but no object created yet
	{
		if (current == Dot)	drawStart(px1, py1, size, c);
		else if (current == Line) 
			{
				if (points.size() == 0 || points.size() % 2 == 0) drawStart(px1, py1, size, c);
				else { drawPoint(points[points.size() - 1]); drawStart(px1, py1, size, c); }
			}
		else
		{
			if (lastMarker == 0 && polygonMarkers.size() > 0)
			{
				if (points.size() == 0) drawStart(px1, py1, size, c);
				else drawPoint(points[lastMarker]);
			}
			for (int i = lastMarker + 1; i < points.size(); i++) drawPoint(points.at(i));
			drawStart(px1, py1, size, c);
		}
	}
	//Checking for the first point on a line before the second point's initial position
	//is defined (Line Mode Only)
	else if (flag1 == false && current != Dot)		
	{
		if (current == Line)
		{
			if (points.size() > 0 && points.size() % 2 != 0) drawPoint(points.at(points.size() - 1));
		}

		else if (current == Polygon)
		{
			if (polygonMarkers.size() > 0)
			{
				if (lastMarker == 0 && points.size() < 1) drawPoint(points.at(0));
				else
				{
					for (int i = lastMarker + 1; i < points.size(); i++) polySet.push_back(points.at(i));
					drawFilledPolygon(polySet);
					polySet.erase(polySet.begin(), polySet.begin() + polySet.size());
				}
			}
		}
	}

	//Drawing the animated objects
	if (current == Dot)
	{
		for (int i = 0; i < points.size(); i++)
		{
			drawPoint(points.at(i));
			if (pauseflag == false) points.at(i).UpdatePosition();
		}
	}
	else if (current == Line)
	{
		//Making sure that the vector limit passed has an even number of Vertex objects
		if (points.size() % 2 == 0) limit = points.size();
		else limit = points.size() - 1;

		for (int i = 0; i < limit; i = i + 2)
		{
			drawVertexLine(points.at(i), points.at(i + 1));
			if (pauseflag == false) { points.at(i).UpdatePosition(); points.at(i + 1).UpdatePosition(); }
		}
	}
	else if (current == Polygon)
	{
		if (polygonMarkers.size() > 1)
		{
			//Drawing the first polygon
			for (int k = polygonMarkers.at(0); k < polygonMarkers.at(1); k++)
			{
				polySet.push_back(points.at(k));
				if (pauseflag == false) points.at(k).UpdatePosition();
			}
			polySet.push_back(points.at(polygonMarkers.at(1)));
			drawFilledPolygon(polySet);
			polySet.erase(polySet.begin(), polySet.begin() + polySet.size());

			//Drawing the remaining polygons
			for (int i = 1; i < polygonMarkers.size(); i++)
			{
				for (int j = polygonMarkers.at(i - 1) + 1; j < polygonMarkers.at(i); j++) 
				{
					polySet.push_back(points.at(j)); 
					if (pauseflag == false) points[j].UpdatePosition();
				}
				polySet.push_back(points.at(polygonMarkers.at(i)));
				drawFilledPolygon(polySet);
				polySet.erase(polySet.begin(), polySet.begin() + polySet.size());
			}
		}
	}

	glFlush();
	
	//Double Buffering
	glutSwapBuffers();
	glutPostRedisplay();
	
}

/*
 * Method: RandomPoints
 * Usage: RandomPoints();
 * ----------------------
 * This method creates Vertex objects with randomized
 * values. The number of objects created is given by 
 * <maxObjects>.
*/

void RandomPoints()
{
	//Number of Vertex objects to create
	int maxObjects = 50;
	int maxPolygons = 10;
	int temp;
	int count;

	srand((unsigned)time(0));
	for (int i = 0; i < maxObjects; i++)
	{
		px1 = (rand() % glutGet(GLUT_SCREEN_WIDTH)) + 1; 
		py1 = (rand() % glutGet(GLUT_SCREEN_HEIGHT)) + 1;
		px2 = (rand() % glutGet(GLUT_SCREEN_WIDTH)) + 1; 
		py2 = (rand() % glutGet(GLUT_SCREEN_HEIGHT)) + 1;

		if (randomflag == true)
		{
			for (int j = 0; j < 3; j++) c[j] = rand() / double(RAND_MAX);
		}

		Vertex p(px1, py1, px2, py2, size, c); 
		points.push_back(p);
		count = points.size();
	}

	if (polygonMarkers.size() == 0) polygonMarkers.push_back(0);

	for (int j = 0; j < maxPolygons - 1; j++)
	{
		temp = (rand() % 5) + 1;
		lastMarker = lastMarker + temp;
		polygonMarkers.push_back(lastMarker);
	}
	polygonMarkers.push_back(points.size() - 1); lastMarker = points.size() - 1;

	return;
}

/*
 * Method: kbd
 * Usage: glutKeyboardFunc(kbd);
 * -----------------------------
 * This function is defined by the programmer to handle all
 * calls to the keyboard functions of GLUT.
 * It responds to the following keys:
 *
 *		Q/q -----> Exits the program
 *		P/p -----> Pauses the animation
 *		R/r -----> Resets the screen
 *		A/a -----> Randomizes new objects
 *	   Space ----> Draws a new animated object (Polygon Mode Only)
 *		 1  -----> Changes the mode to Dot
 *		 2  -----> Changes the mode to Line
 *		 3  -----> Changes the mode to Polygon
 *		 +  -----> Increases the speed of all vertex objects
 *		 -  -----> Decreases the speed of all vertex objects
 *
*/

void kbd(unsigned char key, int x, int y)
{
	//If the "q" key is pressed, quit the program
	if(key == 'q' || key == 'Q') exit(0);

	//If "1" is pressed, enter Dot Mode
	else if (key == '1' && current != Dot) current = Dot;
	
	//If "2" is pressed, enter Line Mode
	else if (key == '2' && current != Line) 
	{
		current = Line;
		if (points.size() % 2 != 0) points.erase(points.begin() + points.size() - 1);
	}
	
	//If "3" is pressed, enter Polygon Mode
	else if (key == '3' && current != Polygon)
	{
		if (points.size() != 0)
		{
			//Ensuring a minimum of three Vertex objects for drawPolygon
			if (points.size() < 3)
			{
				for (int i = points.size(); i < 3; i++)
				{
					px1 = (rand() % glutGet(GLUT_SCREEN_WIDTH)) + 1; 
					py1 = (rand() % glutGet(GLUT_SCREEN_HEIGHT)) + 1;
					
					px2 = (rand() % glutGet(GLUT_SCREEN_WIDTH)) + 1; 
					py2 = (rand() % glutGet(GLUT_SCREEN_HEIGHT)) + 1;

					if (randomflag == true)
					{
						for (int j = 0; j < 3; j++) c[j] = rand() / double(RAND_MAX);
					}

					Vertex p(px1, py1, px2, py2, size, c); points.push_back(p);
				}
			}
			if (polygonMarkers.size() == 1 || polygonMarkers.at(polygonMarkers.size() - 1) != points.size() - 1)
			{
				polygonMarkers.push_back(points.size() - 1);
				lastMarker = points.size() - 1;
			}
		}
		current = Polygon;
	}

	//If "Space" is pressed in Polygon Mode, start animation (set flag)
	else if (key == ' ' && current == Polygon)
	{
		polygonMarkers.push_back(points.size() - 1);
		lastMarker = points.size() - 1;
	}

	//If "r" or "R" is pressed, clear the vertex list
	else if (key == 'r' || key == 'R') points.erase(points.begin(), points.begin() + points.size());

	//If "a" or "A" is pressed, add a set of randomized primitives
	else if (key == 'a' || key == 'A') RandomPoints();

	//If "-" is pressed, decrease the speed of all stored points
	else if (key == '-')
	{
		for (int i = 0; i < points.size(); i++) points.at(i).ChangeSpeed(false);
	}

	//If "+" is pressed, increase the speed of all stored points
	else if (key == '+')
	{
		for (int i = 0; i < points.size(); i++) points.at(i).ChangeSpeed(true);
	}

	//If "p" or "P" is pressed, pause/play the animation
	else if (key == 'p' || key == 'P') pauseflag = !pauseflag;

	return;
}

/*
 * Methods: MainMenu, ColourSubMenu and SizeSubMenu
 * Usage: With GLUT menu options
 * ------------------------------------------------
 * These methods are used with the GLUT menu and submenu functions.
 * They offer menu functionality to change vertex colour and size
 * data. The MainMenu function is an empty function, which allows 
 * the main drop down menu to be comprosed only of submenu options.
 * Each submenu function has two switch statements. This allows for 
 * the program to indicate which options are currently selected.
*/

void MainMenu(int dummy) { return; }

void SizeSubMenu (GLint newSize)
{
	switch(int(size))
	{
		case 1: glutChangeToMenuEntry(1, "1", 1); break;
		case 2: glutChangeToMenuEntry(2, "2", 2); break;
		case 3: glutChangeToMenuEntry(3, "3", 3); break;
		case 4: glutChangeToMenuEntry(4, "4", 4); break;
		case 5: glutChangeToMenuEntry(5, "5", 5); break;
		case 6: glutChangeToMenuEntry(6, "6", 6); break;
		case 7: glutChangeToMenuEntry(7, "7", 7); break;
		case 8: glutChangeToMenuEntry(8, "8", 8); break;
		case 9: glutChangeToMenuEntry(9, "9", 9); break;
		case 10: glutChangeToMenuEntry(10, "10", 10); break;
		default: break;
	}

	size = newSize;
	
	switch(newSize)
	{
		case 1: glutChangeToMenuEntry(1, "> 1", 1); break;
		case 2: glutChangeToMenuEntry(2, "> 2", 2); break;
		case 3: glutChangeToMenuEntry(3, "> 3", 3); break;
		case 4: glutChangeToMenuEntry(4, "> 4", 4); break;
		case 5: glutChangeToMenuEntry(5, "> 5", 5); break;
		case 6: glutChangeToMenuEntry(6, "> 6", 6); break;
		case 7: glutChangeToMenuEntry(7, "> 7", 7); break;
		case 8: glutChangeToMenuEntry(8, "> 8", 8); break;
		case 9: glutChangeToMenuEntry(9, "> 9", 9); break;
		case 10: glutChangeToMenuEntry(10, "> 10", 10); break;
		default: break;
	}

	glutPostRedisplay();

	for (int i = 0; i < points.size(); i++) points.at(i).ChangeSize(size);

	return;
}

void ColourSubMenu(GLint colour)
{
	switch(lastColour)
	{
		case 1: glutChangeToMenuEntry(1, "Red", 1); break;
		case 2: glutChangeToMenuEntry(2, "Green", 2); break;
		case 3: glutChangeToMenuEntry(3, "Blue", 3); break;
		case 4: glutChangeToMenuEntry(4, "Yellow", 4); break;
		case 5: glutChangeToMenuEntry(5, "Cyan", 5); break;
		case 6: glutChangeToMenuEntry(6, "Magenta", 6); break;
		case 7: glutChangeToMenuEntry(7, "White", 7); break;
		case 8: glutChangeToMenuEntry(8, "Random", 8); break;
	}

	randomflag = false;

	switch(colour)
	{
		case 1: 
			glutChangeToMenuEntry(1, "> Red", 1); lastColour = 1;
			c[R] = 1.0; c[G] = 0; c[B] = 0;
			break;
		case 2: 
			glutChangeToMenuEntry(2, "> Green", 2); lastColour = 2;
			c[R] = 0; c[G] = 1.0; c[B] = 0;
			break;
		case 3: 
			glutChangeToMenuEntry(3, "> Blue", 3); lastColour = 3;
			c[R] = 0; c[G] = 0; c[B] = 1.0;
			break;
		case 4: 
			glutChangeToMenuEntry(4, "> Yellow", 4); lastColour = 4;
			c[R] = 1.0; c[G] = 1.0; c[B] = 0;
			break;
		case 5: 
			glutChangeToMenuEntry(5, "> Cyan", 5); lastColour = 5;
			c[R] = 0; c[G] = 1.0; c[B] = 1.0;
			break;
		case 6: 
			glutChangeToMenuEntry(6, "> Magenta", 6); lastColour = 6;
			c[R] = 1.0; c[G] = 0; c[B] = 1.0;
			break;
		case 7: 
			glutChangeToMenuEntry(7, "> White", 7); lastColour = 7;
			c[G] = 1.0; c[G] = 1.0; c[B] = 1.0;
			break;
		case 8: 
			glutChangeToMenuEntry(8, "> Random", 8); lastColour = 8;
			randomflag = true;
			break;
	}
	return;
}

/*
 * Method: Mouse
 * Usage: glutMouseFunc(Mouse);
 * ----------------------------
 * This function handles the data that the GLUT library is able
 * to collect from the mouse. It only processes data if it
 * detects that a mouse button has been pressed, not released.
*/

void Mouse (int button, int state, int x, int y){
	
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		//Detecting the first click of a set of two
		if (flag1 == false)
		{
			px1 = x; py1 = y;

			//Generating a random colour; this will be used to create the 
			//vertex object as well as draw a position indicator
			if (randomflag == true) 
			{
				for (int i = 0; i < 3; i++) c[i] = rand() / double(RAND_MAX);
			}
			else if (points.size() > 50)
			{
			c[0] = 1;
			c[1] = 0;
			c[2] = 0;
			}

			//Initializing the polygon marker vector
			if (polygonMarkers.size() == 0) polygonMarkers.push_back(0);
			flag1 = true;
		}

		//Acknowledges that the first click has occured
		else
		{
			px2 = x; py2 = y;

			//Creates a new Vertex object and adds it to the end of the point list
			Vertex p(px1, py1, px2, py2, size, c); points.push_back(p);

			flag1 = false;
		}
	}

	return;
}

/*		Main Program		*/

int main (int argc, char** argv)
{
	GLint subMenuSize;
	GLint subMenuColour;

	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE);

	//Creating the window
	glutInitWindowSize(500, 500);
	glutCreateWindow("Screen Saver");
	glutFullScreen();
	
	//User input functions
	glutMouseFunc(Mouse);
	glutKeyboardFunc(kbd);

	/*	Menus	*/
	//Size SubMenu
	subMenuSize = glutCreateMenu(SizeSubMenu);
		glutAddMenuEntry ("1", 1);
		glutAddMenuEntry ("2", 2);
		glutAddMenuEntry ("> 3", 3);
		glutAddMenuEntry ("4", 4);
		glutAddMenuEntry ("5", 5);
		glutAddMenuEntry ("6", 6);
		glutAddMenuEntry ("7", 7);
		glutAddMenuEntry ("8", 8);
		glutAddMenuEntry ("9", 9);
		glutAddMenuEntry ("10", 10);

	//Colour SubMenu
	subMenuColour = glutCreateMenu(ColourSubMenu);
		glutAddMenuEntry ("Red", 1);
		glutAddMenuEntry ("Green", 2);
		glutAddMenuEntry ("Blue", 3);
		glutAddMenuEntry ("Yellow", 4);
		glutAddMenuEntry ("Cyan", 5);
		glutAddMenuEntry ("Magenta", 6);
		glutAddMenuEntry ("White", 7);
		glutAddMenuEntry ("> Random", 8);

	//Main Menu
	glutCreateMenu(MainMenu);
		glutAddSubMenu("Size", subMenuSize);
		glutAddSubMenu("Colour", subMenuColour);

	//Attach menu to the right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
		
	//Display functions
	glutDisplayFunc(display);
	glutMainLoop();
	
	return(0);
}

