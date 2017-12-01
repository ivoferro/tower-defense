#pragma once

#include <vector>
#include "../framework/GameObject.h"
#include "../framework/Drawable.h"

class Enemy : public GameObject, Drawable
{

private:
	//LifeBar *lifebar;
	void initEnemy();
	void drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat normal[], GLfloat color[]);
	void setUpCollider();
	void onCollisionEnter(GameObject * collidingObject);
	GLfloat health = 100;

public:
	Enemy();
	~Enemy();
	void draw();
	void timerActions();

	GLboolean isAlive = true;

	std::vector< GLuint > idleFrames;
	GLuint dl;
};

