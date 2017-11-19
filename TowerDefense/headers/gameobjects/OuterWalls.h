#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"
#include "../framework/Drawable.h"

class OuterWalls : public GameObject, Drawable
{

public:
	OuterWalls();
	~OuterWalls();
	void draw();
	void drawWalls(GLfloat width, GLfloat height);
	void OuterWalls::drawDoor(GLfloat color[3]);
};

