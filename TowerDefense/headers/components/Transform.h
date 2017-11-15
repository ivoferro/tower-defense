#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/Component.h"

class Transform : public Component
{

public:
	Transform();
	
	class Coordinates
	{
	public:
		Coordinates();
		Coordinates(GLfloat x, GLfloat y, GLfloat z);
		GLfloat x;
		GLfloat y;
		GLfloat z;
	};

	Coordinates * position;
	Coordinates * rotation;
	Coordinates * scale;

};

