#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"
#include "../framework/Drawable.h"

class Ground : public GameObject, Drawable
{

public:
	Ground();
	~Ground();
	void draw();

};

