/*
 * Geneva Smith
 * File: particle_class.h
 * ---------------------------------------------------------
 * A class designed to handle particle specific functions
 * and behaviours. This class affects a single particle.
 */

class Particle
{
	public:
		// Constructor and Destructor
		Particle(int initSize);
		~Particle();

		// Getters
		float GetXLocation();
		float GetYLocation();
		float GetZLocation();

		float GetXDirection();
		float GetYDirection();
		float GetZDirection();

		float GetXSpin();
		float GetYSpin();
		float GetZSpin();

		int GetSize();

		float GetRed();
		float GetGreen();
		float GetBlue();

		int GetAge();

		float GetGravity();

		// Mutators
		void IncrementAge(int step);
		void ParticleStep();
		void Bounce();
		void Friction(double factor);
		void SetColour(double R, double G, double B);

		void SetGravity(float newGravity);
		void ResetGravity();

	private:
		#include "particle_priv.h"
};