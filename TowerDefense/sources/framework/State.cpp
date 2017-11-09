#include "../../headers/framework/State.h"

State::State()
{
	doubleBuffer = GL_TRUE;
	movementDelay = 20;
}

GLboolean State::isDoubleBufferActivated()
{
	return doubleBuffer;
}

GLint State::getMovementDelay()
{
	return movementDelay;
}
