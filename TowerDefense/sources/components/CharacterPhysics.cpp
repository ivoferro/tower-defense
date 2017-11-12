#include "../../headers/components/CharacterPhysics.h"

CharacterPhysics::CharacterPhysics()
{
	velocity = 0;
	maxFrontVelocity = 0.3;
	maxBackVelocity = 0.3;

	sideVelocity = 0;
	maxSideVelocity = 0.2;
}

CharacterPhysics::~CharacterPhysics()
{
}
