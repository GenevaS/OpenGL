struct planet
{
	double radius;
	double orbitRadius;
	double orbitPeriod;
	double axisAng;
	double axisPeriod;

	double cAxisAng;
	double cOrbitAng;
};

void DrawSphere(double radius);
void DrawPlanet(planet plan);
planet Update(planet plan);