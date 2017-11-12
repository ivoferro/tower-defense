#include "../../headers/framework/State.h"

State::State()
{
	doubleBuffer = GL_TRUE;
	movementDelay = 20;
	inputs = new Inputs();
	mousePositionX = 0;
	mousePositionY = 0;
}

GLboolean State::isDoubleBufferActivated()
{
	return doubleBuffer;
}

GLint State::getMovementDelay()
{
	return movementDelay;
}

Inputs * State::getInputs()
{
	return inputs;
}