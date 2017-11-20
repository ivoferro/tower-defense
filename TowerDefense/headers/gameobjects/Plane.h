#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"
#include "../framework/Drawable.h"

class Plane : public GameObject, public Drawable
{

private:
	std::string textureID;

public:
	Plane(std::string textureID);
	~Plane();
	void draw();

};

