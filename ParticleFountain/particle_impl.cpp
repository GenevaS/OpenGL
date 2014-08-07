/*
 * Geneva Smith
 * File: particle_impl.cpp
 * ---------------------------------------------------------
 * The implementation of the particle functions defined in
 * the particle class.
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "particle_class.h"

using namespace std;

/*
 * Construtor and Destructor
 */
Particle::Particle(int initSize)
{
	// Initial location
	loc.x = 0;
	loc.y = 0;
	loc.z = 0;

	// Initial direction
	dir.x = rand()%10001;
	dir.x = (dir.x-5000)/100000;

	dir.y = rand()%10001;
	dir.y = (dir.y-5000)/100000;

	dir.z = 1;

	// Initial spin/rotation
	spin.x = rand()%360;
	spin.y = rand()%360;
	spin.z = rand()%360;

	// Initial size
	size = initSize;

	// Inital color
	c.r = rand()%10001;
	c.r = c.r/10000;

	c.g = rand()%10001;
	c.g = c.g/10000;

	c.b = rand()%10001;
	c.b = c.b/10000;

	// Initial age
	age = 0;

	// Initial gravity
	gravity = -0.00245;
	initGravity = -0.00245;

	return;
}

Particle::~Particle()
{
	return;
}

/*
 * Get Location 
 * ----------------------------------------------------------------------------------------
 * Set of functions to return information from the location data structure without the need
 * for the main program to know what the structure is.
 */
float Particle::GetXLocation()
{
	return loc.x;
}

float Particle::GetYLocation()
{
	return loc.y;
}

float Particle::GetZLocation()
{
	return loc.z;
}

/*
 * Get Direction
 * ----------------------------------------------------------------------------------------
 * Set of functions to return information from the direction data structure without the need
 * for the main program to know what the structure is.
 */
float Particle::GetXDirection()
{
	return dir.x;
}

float Particle::GetYDirection()
{
	return dir.y;
}

float Particle::GetZDirection()
{
	return dir.z;
}

/*
 * Bounce
 * ----------------------------------------------------------------------------------------
 * Invert the Z location and direction of the particle
 */
void Particle::Bounce()
{
	loc.z *= -1;
	dir.z *= -1;
	return;
}

void Particle::Friction(double factor)
{
	dir.z *= factor;
	return;
}

/*
 * Get Spin
 * ----------------------------------------------------------------------------------------
 * Set of functions to return information from the spin data structure without the need
 * for the main program to know what the structure is.
 */
float Particle::GetXSpin()
{
	return spin.x;
}

float Particle::GetYSpin()
{
	return spin.y;
}

float Particle::GetZSpin()
{
	return spin.z;
}

/*
 * Get Size
 * ----------------------------------------------------------------------------------------
 * Return the size of the particle.
 */

int Particle::GetSize()
{
	return size;
}

/*
 * Get Colour
 * ----------------------------------------------------------------------------------------
 * Set of functions to return information from the colour data structure without the need
 * for the main program to know what the structure is.
 */
float Particle::GetRed()
{
	return c.r;
}

float Particle::GetGreen()
{
	return c.g;
}

float Particle::GetBlue()
{
	return c.b;
}

/*
 * Get Age
 * ----------------------------------------------------------------------------------------
 * Return the age of the particle.
 */

int Particle::GetAge()
{
	return size;
}

/* 
 * IncrementAge
 * -----------------------------------------------------------------------------------------
 * Increment the particle age by <step> amount.
 */

void Particle::IncrementAge(int step)
{
	age += step;

	return;
}

/*
 * ParticleStep
 * ----------------------------------------------------------------------------------------
 * Calculates the next position of particle in time.
 */
void Particle::ParticleStep()
{
	dir.z += gravity;

	loc.x += dir.x;
	loc.y += dir.y;
	loc.z += dir.z;

	return;
}

/*
 * Gravity Functions
 * ----------------------------------------------------------------------------------------
 * Allow the user to see the current gravity value, set it to a custom value, or reset it
 * to the default gravity.
 */

float Particle::GetGravity()
{
	return gravity;
}

void Particle::SetGravity(float newGravity)
{
	gravity = newGravity;
	return;
}

void Particle::ResetGravity()
{
	gravity = initGravity;
	return;
}

/*
 * Colour Functions
 * -----------------------------------------------------------------------------------------
 * Allow the user to manually control the colour of the particle.
 */

void Particle::SetColour(double R, double G, double B)
{
	c.r = R;
	c.g = G;
	c.b = B;

	return;
}