#ifndef Camera_h
#define Camera_h

class Camera
{
public:

	Camera(double step);
	~Camera();

	void RotateCamera(double x, double y);

	void MoveCameraForward();
	void MoveCameraBack();
	void MoveCameraLeft();
	void MoveCameraRight();

	void UseCamera();

private:
	
	#include "Camerapriv.h"
};

#endif