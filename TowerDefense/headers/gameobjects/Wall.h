#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"

class Wall : public GameObject
{

private:
	void drawCube();
	void drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat normal[]);
	void setUpCollider();
	void onCollisionEnter(GameObject * collidingObject) override;

public:
	Wall();
	~Wall();
	void draw();

};

