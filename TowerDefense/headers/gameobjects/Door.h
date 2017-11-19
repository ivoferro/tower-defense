#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"
#include "../framework/Drawable.h"

class Door : public GameObject, Drawable
{

private:
	void drawCube();
	void drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat cor[]);

public:
	Door();
	~Door();
	void draw();

};

