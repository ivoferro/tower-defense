#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"
#include "../framework/Drawable.h"
#include "../components/Transform.h"
#include "../components/MDLModel.h"

class Player : public GameObject, Drawable
{
	
private:
	MDLModel* model;
	GLint timer;
	void setUpCollider();
	void onCollisionEnter(GameObject * collidingObject) override;
	void initModel();
	void drawModel();

	Transform oldTransform;

public:
	Player();
	~Player();
	void draw();
	void timerActions(int value);
	void animate();
	void move();
	GLboolean isColliding;
};

