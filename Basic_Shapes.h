#ifndef _Basic_Shapes_h
#define _Basic_Shapes_h

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#include "vertex.h"

using namespace std;

void drawPoint(Vertex point);

void drawStart(double x, double y, int size, double colour[3]);

void drawLine(double p1[2], double c1[3], double p2[2], double c2[3]);

void drawVertexLine(Vertex point1, Vertex point2);

void drawQuad(double p1[2], double p2[2], double p3[2], double p4[2], double c[3]);

void drawRectangle(double c[2], double w, double h, double colour[3]);

void drawCircle(double c[2], double r, double colour[3]);

void drawFilledPolygon(vector <Vertex> corners);

#endif
