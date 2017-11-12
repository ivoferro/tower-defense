#include "../../headers/gameobjects/Camera.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/CameraSettings.h"

Camera::Camera()
{
	addComponent("transform", new Transform());
	addComponent("settings", new CameraSettings());
}

Camera::~Camera()
{
}