#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"

class Player : public GameObject
{
	
private:
	void drawCube();
	void drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat cor[]);

public:
	Player();
	~Player();
	void draw();

};

