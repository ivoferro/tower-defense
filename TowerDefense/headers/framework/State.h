#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "Inputs.h"

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
	Inputs * inputs;

public:
	State();

	GLboolean isDoubleBufferActivated();
	GLint getMovementDelay();
	CameraType getCameraType();
	Inputs * getInputs();

	int mousePositionX;
	int mousePositionY;

};