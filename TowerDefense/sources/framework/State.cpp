#include "../../headers/framework/State.h"

State::State()
{
	doubleBuffer = GL_TRUE;
	movementDelay = 20;
	cameraType = CameraType::PERSPECTIVE;
}

GLboolean State::isDoubleBufferActivated()
{
	return doubleBuffer;
}

GLint State::getMovementDelay()
{
	return movementDelay;
}

State::CameraType State::getCameraType()
{
	return cameraType;
}
