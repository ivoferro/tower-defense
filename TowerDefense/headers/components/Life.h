#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/Component.h"

class Life : public Component
{
public:
	Life();
	~Life();

	GLfloat health;
};

