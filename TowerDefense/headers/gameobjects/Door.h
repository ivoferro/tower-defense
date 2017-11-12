#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"

class Door : public GameObject
{

private:
	void drawCube();
	void drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat cor[]);

public:
	Door();
	~Door();
	void draw();

};

