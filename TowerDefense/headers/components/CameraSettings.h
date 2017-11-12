#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/Component.h"

class CameraSettings : public Component
{

public:
	CameraSettings();
	~CameraSettings();

	enum CameraType
	{
		ORTHO,
		PERSPECTIVE
	};

	CameraType cameraType;

	GLfloat fieldOfView;

	GLfloat distanceFromTarget;
	GLfloat minDistanceFromTarget;
	GLfloat maxDistanceFromTarget;

};

