#pragma once

#include <stdlib.h>
#include <GL/glut.h>

class State
{

private:
	GLboolean doubleBuffer;
	GLint movementDelay;

public:
	State();

	GLboolean isDoubleBufferActivated();
	GLint getMovementDelay();

};