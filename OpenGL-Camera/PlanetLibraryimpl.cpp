#include <gl/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <cmath>
#include <iostream>

#include "PlanetLibrary.h"

const int SLICES = 15;
const int STACKS = 15;

planet sun;
planet merc, ven, ear, mars, jup, sat, urn, nep, plu;

void initPlanets()
{
	sun.axisAng = 0;
	sun.axisPeriod = 0.1;
	sun.orbitPeriod = 0;
	sun.orbitRadius = 0;
	sun.radius = 20;
	sun.cAxisAng = 0;
	sun.cOrbitAng = 0;

	merc.axisAng = 0;
	merc.axisPeriod = 24 / (175.94 * 24);
	merc.orbitPeriod = 360 / (0.24 * 360);
	merc.orbitRadius = 40;
	merc.radius = 1;
	merc.cAxisAng = 0;
	merc.cOrbitAng = 0;

	ven.axisAng = 177;
	ven.axisPeriod = -24 / (116.75 * 24);
	ven.orbitPeriod = 360 / (0.62 * 360);
	ven.orbitRadius = 80;
	ven.radius = 2;
	ven.cAxisAng = 0;
	ven.cOrbitAng = 0;

	ear.axisAng = 23.5;
	ear.axisPeriod = 24 / (1 * 24);
	ear.orbitPeriod = 360 / (1 * 360);
	ear.orbitRadius = 100;
	ear.radius = 2;
	ear.cAxisAng = 0;
	ear.cOrbitAng = 0;

	mars.axisAng = 25;
	mars.axisPeriod = 24 / (1.03 * 24);
	mars.orbitPeriod = 360 / (1.88 * 360);
	mars.orbitRadius = 120;
	mars.radius = 1.5;
	mars.cAxisAng = 0;
	mars.cOrbitAng = 0;

	jup.axisAng = 3;
	jup.axisPeriod = 24 / (0.41 * 24);
	jup.orbitPeriod = 360 / (11.86 * 360);
	jup.orbitRadius = 160;
	jup.radius = 5;
	jup.cAxisAng = 0;
	jup.cOrbitAng = 0;

	sat.axisAng = 27;
	sat.axisPeriod = 24 / (0.43 * 24);
	sat.orbitPeriod = 360 / (29.46 * 360);
	sat.orbitRadius = 190;
	sat.radius = 4;
	sat.cAxisAng = 0;
	sat.cOrbitAng = 0;

	urn.axisAng = 98;
	urn.axisPeriod = 24 / (-0.72 * 24);
	urn.orbitPeriod = 360 / (84.01 * 360);
	urn.orbitRadius = 210;
	urn.radius = 3;
	urn.cAxisAng = 0;
	urn.cOrbitAng = 0;

	nep.axisAng = 30;
	nep.axisPeriod = 24 / (0.67 * 24);
	nep.orbitPeriod = 360 / (164.8 * 360);
	nep.orbitRadius = 230;
	nep.radius = 3;
	nep.cAxisAng = 0;
	nep.cOrbitAng = 0;

	plu.axisAng = 118;
	plu.axisPeriod = 24 / (-6.39 * 24);
	plu.orbitPeriod = 360 / (248.09 * 360);
	plu.orbitRadius = 260;
	plu.radius = 1;
	plu.cAxisAng = 0;
	plu.cOrbitAng = 0;

	return;
}

void DrawSun()
{
	GLUquadricObj *sphere;
	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FILL);

	//Texture the sphere
	gluQuadricTexture(sphere, GL_TRUE);

	//Point normals outwards for lighting
	gluQuadricOrientation(sphere, GLU_OUTSIDE);

	//Turn the sphere right way up before drawing
	glPushMatrix();

	glRotated(sun.cAxisAng, 0, 1, 0);
	glRotated(-90, 1, 0, 0);

	//Draw
	gluSphere(sphere, sun.radius, SLICES, STACKS);
	glPopMatrix();

	return;
}

void DrawMercury()
{
	DrawPlanet(merc);

	return;
}

void DrawVenus()
{
	DrawPlanet(ven);

	return;
}

void DrawEarth()
{
	DrawPlanet(ear);

	return;
}

void DrawMars()
{
	DrawPlanet(mars);

	return;
}

void DrawJupiter()
{
	DrawPlanet(jup);

	return;
}

void DrawSaturn()
{
	DrawPlanet(sat);

	return;
}

void DrawUranus()
{
	DrawPlanet(urn);

	return;
}

void DrawNeptune()
{
	DrawPlanet(nep);

	return;
}

void DrawPluto()
{
	DrawPlanet(plu);

	return;
}
//Wrapper function for updating the planet's angles
void UpdatePlanets()
{
	sun = Update(sun);
	merc = Update(merc);
	ven = Update(ven);
	ear = Update(ear);
	mars = Update(mars);
	jup = Update(jup);
	sat = Update(sat);
	urn = Update(urn);
	nep = Update(nep);
	plu = Update(plu);

	return;
}

//Update function for orbit and axis angles
planet Update(planet plan)
{
	plan.cAxisAng += plan.axisPeriod;
	if (abs(plan.cAxisAng) > 360) 
	{
		if (plan.cAxisAng > 0) plan.cAxisAng -= 360;
		else plan.cAxisAng += 360;
	}

	plan.cOrbitAng += plan.orbitPeriod;
	if (abs(plan.cOrbitAng) > 360) 
	{
		if (plan.cOrbitAng > 0) plan.cOrbitAng -= 360;
		else plan.cOrbitAng += 360;
	}

	return plan;
}

void DrawRings()
{
	GLUquadricObj *rings;
	rings = gluNewQuadric();

	gluQuadricDrawStyle(rings, GLU_FILL);

	//Point normals outwards for lighting
	gluQuadricOrientation(rings, GLU_OUTSIDE);

	//Texture the rings
	gluQuadricTexture(rings, GL_TRUE);

	glRotated(80, 0, 0, 1);

	gluDisk(rings, 4.3, 8, 10, 3);

	return;
}

//Drawing of the planets
void DrawPlanet(planet plan)
{
	glRotated(plan.cAxisAng, 0, 1, 0);
	glRotated(plan.axisAng, 1, 0, 0);
	glTranslated(plan.orbitRadius, 0, 0);
	glRotated(plan.cOrbitAng, 0, 1, 0);

	DrawSphere(plan.radius);

	return;
}

//Drawing spheres to represent planets
void DrawSphere(double radius)
{
	GLUquadricObj *sphere;
	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FILL);

	//Point normals outwards for lighting
	gluQuadricOrientation(sphere, GLU_OUTSIDE);

	//Texture the sphere
	gluQuadricTexture(sphere, GL_TRUE);

	//Turn the sphere right way up before drawing
	glRotated(-90, 1, 0, 0);

	//Draw
	gluSphere(sphere, radius, SLICES, STACKS);

	return;
}