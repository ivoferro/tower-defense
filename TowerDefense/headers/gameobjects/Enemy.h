#pragma once

#include <vector>
#include "../framework/GameObject.h"
#include "../framework/Drawable.h"
#include "../components/MDLModel.h"
#include "LifeBar.h"

class Enemy : public GameObject, Drawable
{

private:
	LifeBar * lifebar;
	MDLModel* model;
	void initModel();
	void drawModel();
	void setUpCollider();
	void onCollisionEnter(GameObject * collidingObject);

public:
	Enemy();
	~Enemy();
	void draw();
	void timerActions();
	void animate();

	GLboolean isAlive = true;
};

