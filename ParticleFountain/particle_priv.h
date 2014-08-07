/*
 * Geneva Smith
 * File: particle_priv.h
 * ---------------------------------------------------------
 * The private data of the particle class. Should not be 
 * used directly unless you are modifying the particle
 * class itself.
 */

// Particle Data Structures
struct location
{
	float x;
	float y;
	float z;
};

struct direction
{
	float x;
	float y;
	float z;
};

struct rotation
{
	float x;
	float y;
	float z;
};

struct color 
{
	float r;
	float g;
	float b;
};

// Paricle Data
location loc;
direction dir;
rotation spin;
int size;
color c;
int age;

float initGravity;
float gravity;