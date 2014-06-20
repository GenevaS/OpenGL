/*
 * Solar System
 * Geneva Smith
 * Fall 2011
*/

#include <windows.h>
#include <stdio.h>
#include <gl/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>

#include "PPMTextureLoader.h"
#include "PlanetLibrary.h"
#include "Camera.h"

using namespace std;

int ang = 0;	//angle for rotating cube
int cnt = 0;

GLuint texID[11];

GLfloat light0pos[] = {0, 0, 0, 1};
Camera cam(0.5);

void DrawPlanets()
{
	//Sun
	glBindTexture(GL_TEXTURE_2D, texID[10]);
	glPushMatrix();
	DrawSun();
	glPopMatrix();

	//Mercury
	glBindTexture(GL_TEXTURE_2D, texID[0]);
	glPushMatrix();
	DrawMercury();
	glPopMatrix();

	//Venus
	glBindTexture(GL_TEXTURE_2D, texID[1]);
	glPushMatrix();
	DrawVenus();
	glPopMatrix();

	//Earth
	glBindTexture(GL_TEXTURE_2D, texID[2]);
	glPushMatrix();
	DrawEarth();
	glPopMatrix();

	//Mars
	glBindTexture(GL_TEXTURE_2D, texID[3]);
	glPushMatrix();
	DrawMars();
	glPopMatrix();

	//Jupiter
	glBindTexture(GL_TEXTURE_2D, texID[4]);
	glPushMatrix();
	DrawJupiter();
	glPopMatrix();

	//Saturn
	glBindTexture(GL_TEXTURE_2D, texID[5]);
	glPushMatrix();
	DrawSaturn();
	glBindTexture(GL_TEXTURE_2D, texID[9]);
	DrawRings();
	glPopMatrix();

	//Uranus
	glBindTexture(GL_TEXTURE_2D, texID[6]);
	glPushMatrix();
	DrawUranus();
	glPopMatrix();

	//Neptune
	glBindTexture(GL_TEXTURE_2D, texID[7]);
	glPushMatrix();
	DrawNeptune();
	glPopMatrix();

	//Pluto (Yes, Pluto too)
	glBindTexture(GL_TEXTURE_2D, texID[8]);
	glPushMatrix();
	DrawPluto();
	glPopMatrix();

	return;
}

void DrawStars()
{
	double x, y;
	double z = 99;

	glBegin(GL_POINTS);
	glColor3d(1, 1, 1);
	for (int i = 0; i < 100; i++)
	{
		glVertex3d(rand() % 100 + 1, rand() % 100 + 1, z);
	}
	glEnd();
}

/* display() - the OpenGL display function, this draws the screen
 */
void display()
{
	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cnt++;

	//increment the rotation angle every 100th display cycle
	if(cnt % 100 == 0)
	{
		UpdatePlanets();
		cnt = 0;
	}

	cam.UseCamera();
	glPushMatrix();

		DrawPlanets();

	glPopMatrix();

	//DrawStars();

	glFlush();

	glutSwapBuffers();
	glutPostRedisplay();
}

void Help()
{
	cout << endl << endl;
	cout << "Welcome to the Starship Enterprise! We are going to take you on a journey ";
	cout << "through the Solar System. Please be aware that the planets are moving exceptionally ";
	cout << "fast today, and you may not be able to catch up to them. Mercury and Venus seem to ";
	cout << "run into some motor troubles, so you can get a good look at them if you wish." << endl;
	cout << "Please do not be alarmed if you cannot see the stars - they are having a nap." << endl;
	cout << endl;
	cout << "The ship can be controlled as follows: " << endl;
	cout << endl;
	cout << "H/h -> Ship controls" << endl;
	cout << "W/w -> Move forward" << endl;
	cout << "S/s -> Move backward" << endl;
	cout << "A/a -> Move left" << endl;
	cout << "D/d -> Move right" << endl;
	cout << "Mouse -> Turn ship" << endl;
	cout << endl;
	cout << "Live long and prosper!" << endl;
	cout << endl;

	return;
}

/* kbd -- the GLUT keyboard function 
 *  key -- the key pressed
 *  x and y - mouse x and y coordinates at the time the function is called
 */
void kbd(unsigned char key, int x, int y)
{
	//if the "q" key is pressed, quit the program
	if(key == 'q' || key == 'Q') exit(0);

	if(key == 'w' || key == 'W') cam.MoveCameraForward();
	if(key == 's' || key == 'S') cam.MoveCameraBack();
	if(key == 'a' || key == 'A') cam.MoveCameraLeft();
	if(key == 'd' || key == 'D') cam.MoveCameraRight();

	if (key == 'h' || key == 'H') Help();
}

void move (int x, int y)
{
	cam.RotateCamera(x, y);

	return;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Starship Enterprise");

	//Initialize planetary data
	initPlanets();

	//Enable and load textures - part of the PPMTextureLoader library
	LoadTextures(texID);
	Help();

	//enable Z buffer test, otherwise things appear in the order they're drawn
	glEnable(GL_DEPTH_TEST);

	//Lighting
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glEnable(GL_LIGHT0);

	//Backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Initial scene view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 1, 100);
	
	//Set clear colour to black
	glClearColor(0, 0, 0, 0);

	//Set the current matrix
	glMatrixMode(GL_MODELVIEW);

	//register glut callbacks for keyboard and display function
	glutKeyboardFunc(kbd);
	glutPassiveMotionFunc(move);
	glutDisplayFunc(display);

	//Run system
	glutMainLoop();

	return 0;
}