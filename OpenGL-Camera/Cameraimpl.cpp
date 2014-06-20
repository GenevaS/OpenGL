#include <iostream>
#include <math.h>

#include <gl/glut.h>
#include <gl/gl.h>

#include "Camera.h"

using namespace std;

const double PI = 22 / 7;

Camera::Camera(double step)
{
	eye[0] = 0;
	eye[1] = 0;
	eye[2] = -15;

	look[0] = 0;
	look[1] = 0;
	look[2] = 1;

	up[0] = 0;
	up[1] = 1;
	up[2] = 0;

	right[0] = 1;
	right[1] = 0;
	right[2] = 0;

	siderot = 0;
	uprot = 0;

	lastX = 0;
	lastY = 0;

	stepsize = abs(step);

	return;
}

Camera::~Camera()
{
	/*	Empty	*/
}

void Camera::RotateCamera(double x, double y)
{
	double radAng, rAng;

	int xNew = x - lastX;
	int yNew = y - lastY;

	if (xNew != 0) 
	{
		siderot += xNew;
		if (siderot >= 360)
		{
			siderot -=360;
		}

		radAng = siderot * PI / 180;
		rAng = (siderot + 90) * PI / 180;

		look[0] = sin(radAng);
		look[2] = cos(radAng);

		right[0] = sin(rAng);
		right[2] = cos(rAng);

		lastX = x;
	}

	if (yNew != 0) 
	{
		//uprot += yNew;
		//look[1] += yNew;
		lastY = y;
	}

	return;
}

void Camera::MoveCameraForward()
{
	eye[0] += stepsize * look[0];
	eye[2] += stepsize * look[2];

	return;
}

void Camera::MoveCameraBack()
{
	eye[0] -= stepsize * look[0];
	eye[2] -= stepsize * look[2];

	return;
}

void Camera::MoveCameraLeft()
{
	eye[0] += stepsize * right[0];
	eye[2] += stepsize * right[2];

	return;
}

void Camera::MoveCameraRight()
{
	eye[0] -= stepsize * right[0];
	eye[2] -= stepsize * right[2];

	return;
}

void Camera::UseCamera()
{
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], look[0] + eye[0], look[1] + eye[1], look[2] + eye[2], 0, 1, 0);

	return;
}