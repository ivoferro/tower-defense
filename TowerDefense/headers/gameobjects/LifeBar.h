#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"

class LifeBar : public GameObject
{

private:
	void drawLifeBar(GLfloat color[]);
	void drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat normal[], GLfloat color[]);


public:
	LifeBar();
	~LifeBar();
	void draw();
	
};

