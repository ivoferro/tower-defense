#pragma once

#include "../framework/GameObject.h"

class Camera : public GameObject
{

public:
	Camera();
	Camera(GLfloat fieldOfView);
	~Camera();

	GLfloat fieldOfView;
};

