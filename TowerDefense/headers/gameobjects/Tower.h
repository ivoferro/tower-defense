#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"
#include "../framework/Drawable.h"

class Tower : public GameObject, Drawable
{

private:
	void drawTower();
	void setUpCollider();
	void onCollisionEnter(GameObject * collidingObject) override;
	
public:
	Tower();
	~Tower();
	void draw();
	void initModel();
};

