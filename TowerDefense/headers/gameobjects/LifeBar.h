#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"
#include "../framework/Drawable.h"
#include "../components/Life.h"

class LifeBar : public GameObject, Drawable
{

private:
	GameObject * parent;
	GLfloat offSetUp;
	GLfloat rotationOffSet;
	void drawLifeBar(GLfloat color[]);
	void drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat normal[], GLfloat color[]);

public:
	LifeBar(GameObject * parent, GLfloat offSetUp, GLfloat rotationOffSet);
	~LifeBar();
	void draw();

};

