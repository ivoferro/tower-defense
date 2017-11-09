#pragma once

#include <stdlib.h>
#include <GL/glut.h>

class State
{

public:
	enum CameraType
	{
		ORTHO,
		PERSPECTIVE
	};

private:
	GLboolean doubleBuffer;
	GLint movementDelay;
	CameraType cameraType;

public:
	State();

	GLboolean isDoubleBufferActivated();
	GLint getMovementDelay();
	CameraType getCameraType();
};