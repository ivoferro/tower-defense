#pragma once

#include "../framework/GameObject.h"

class Enemy : public GameObject
{
private:
	//LifeBar *lifebar;
	void drawEnemy();
	void drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat cor[]);
	void setUpCollider();
	void onCollisionEnter(GameObject * collidingObject);

public:
	Enemy();
	~Enemy();
	void draw();
};

