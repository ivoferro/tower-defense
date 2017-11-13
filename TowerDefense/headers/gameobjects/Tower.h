#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"

class Tower : public GameObject
{

private:
	void drawTower();

public:
	Tower();
	~Tower();
	void draw();

};

