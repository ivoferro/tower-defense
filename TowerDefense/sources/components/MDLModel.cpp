#include "../../headers/components/MDLModel.h"

MDLModel::MDLModel()
{
	isInit = GL_FALSE;
	isWalking = GL_FALSE;
	state = Idle;
}

MDLModel::~MDLModel()
{
}

void MDLModel::idle()
{
	state = Idle;
}

void MDLModel::walk()
{
	state = Walking;
}

void MDLModel::sideWalk()
{
	state = SideWalking;
}

void MDLModel::attack()
{
	state = Attacking;
}