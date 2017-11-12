#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/Component.h"

class CharacterPhysics : public Component
{

public:
	CharacterPhysics();
	~CharacterPhysics();

	GLfloat velocity;
	GLfloat maxFrontVelocity;
	GLfloat maxBackVelocity;
	
	GLfloat sideVelocity;
	GLfloat maxSideVelocity;

};