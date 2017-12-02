#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"

class SkyBox : public GameObject
{

private:
	void drawBack();
	void drawFront();
	void drawLeft();
	void drawRight();
	void drawUp();

public:
	SkyBox();
	~SkyBox();
	void draw();

};