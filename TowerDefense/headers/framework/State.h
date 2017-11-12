#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "Inputs.h"

class State
{

private:
	GLboolean doubleBuffer;
	GLint movementDelay;
	Inputs * inputs;

public:
	State();

	GLboolean isDoubleBufferActivated();
	GLint getMovementDelay();
	Inputs * getInputs();

	int mousePositionX;
	int mousePositionY;

};