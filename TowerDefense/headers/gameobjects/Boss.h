#pragma once

#include "../framework/GameObject.h"
#include "../framework/Drawable.h"
#include "../components/MDLModel.h"
#include "LifeBar.h"

class Boss : public GameObject, public Drawable
{

private:
	LifeBar * lifebar;
	void setUpCollider();
	void onCollisionEnter(GameObject * collidingObject);

public:
	Boss();
	~Boss();
	MDLModel* model;
	void draw();
	void timerActions();
	void animate();

};