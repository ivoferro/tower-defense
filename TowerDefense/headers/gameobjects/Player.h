#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"
#include "../framework/Drawable.h"
#include "../components/Transform.h"

class Player : public GameObject, Drawable
{
	
private:
	void drawCube(GLfloat color[]);
	void drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat normal[], GLfloat color[]);
	void setUpCollider();
	void onCollisionEnter(GameObject * collidingObject) override;

	Transform oldTransform;

public:
	Player();
	~Player();
	void draw();

	void timerActions();
	void move();
	GLboolean isColliding;

};

