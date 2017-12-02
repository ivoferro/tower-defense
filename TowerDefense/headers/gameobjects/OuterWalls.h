#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"

class OuterWalls : public GameObject
{

private:
	void setUpCollider();

public:
	OuterWalls();
	~OuterWalls();

};

