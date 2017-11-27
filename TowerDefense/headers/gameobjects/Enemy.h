#pragma once

#include "../framework/GameObject.h"
#include "../framework/Drawable.h"

class Enemy : public GameObject, Drawable
{

private:
	//LifeBar *lifebar;
	void drawEnemy();
	void drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat normal[], GLfloat color[]);
	void setUpCollider();
	void onCollisionEnter(GameObject * collidingObject);

public:
	Enemy();
	~Enemy();
	void draw();
	void timerActions();

};

