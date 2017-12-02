#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"
#include "../framework/Drawable.h"
#include "LifeBar.h"

class Tower : public GameObject, Drawable
{

private:
	LifeBar * lifebar;
	void setUpCollider();
	void onCollisionEnter(GameObject * collidingObject) override;
	
	GLuint prevAttack;


public:
	Tower();
	~Tower();
	void draw();
	void initModel();

	GLboolean gameover;
};

