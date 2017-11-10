#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"

class Ground : public GameObject
{

public:
	Ground();
	~Ground();
	void draw();

};

