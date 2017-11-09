#include "../../headers/gameobjects/Camera.h"
#include "../../headers/components/Transform.h"

Camera::Camera()
{
	fieldOfView = 60;
	addComponent("transform", new Transform());
}

Camera::Camera(GLfloat theFieldOfView)
{
	fieldOfView = theFieldOfView;
	addComponent("transform", new Transform());
}

Camera::~Camera()
{
}