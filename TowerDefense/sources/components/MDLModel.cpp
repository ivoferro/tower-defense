#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/components/MDLModel.h"

MDLModel::MDLModel(int idle, int walk, int sideWalk, int attack, int death, int dead, char *filename)
{
	idleNum = idle;
	walkNum = walk;
	sideWalkNum =sideWalk;
	attackNum = attack;
	deathNum = death;
	deadNum = dead;

	file = (char*)malloc(sizeof(char) * (strlen(filename) + 1));
	strcpy(file, filename);

	isInit = GL_FALSE;
	state = Idle;

	shooting = GL_FALSE;
	startedShooting = 0;

	dying = GL_FALSE;
	startedDying = 0;
}

MDLModel::~MDLModel()
{
}

void MDLModel::init()
{
	if (isInit == GL_FALSE)
	{
		mdlviewer_init(file, model);
		isInit = GL_TRUE;
	}
}

void MDLModel::draw()
{
	mdlviewer_display(model);
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

void MDLModel::attack(GLuint time)
{
	startedShooting = time;
	state = Attacking;
	shooting = GL_TRUE;
}

GLboolean MDLModel::stillShooting(GLuint time, GLuint frameSize)
{
	if (shooting && (time - startedShooting) < frameSize)
	{
		return shooting;
	}
	shooting = GL_FALSE;
	return shooting;
}

void MDLModel::death(GLuint time)
{
	if (!dying)
	{
		startedDying = time;
		state = Death;
		dying = GL_TRUE;
	}
}

GLboolean MDLModel::stillDying(GLuint time, GLuint frameSize)
{
	if (dying && (time - startedDying) < frameSize)
	{
		return dying;
	}
	dying = GL_FALSE;
	return dying;
}

void MDLModel::dead()
{
	if (model.GetSequence() != deadNum)
	{
		model.SetSequence(deadNum);
	}
}

void MDLModel::animate()
{
	if (isInit)
	{
		if (model.GetSequence() == deadNum)
		{
			return;
		}

		switch (state)
		{
		case Death:
			if (model.GetSequence() != deathNum)
			{
				model.SetSequence(deathNum);
			}
			break;
		case Walking:
			if (model.GetSequence() != walkNum)
			{
				model.SetSequence(walkNum);
			}
			break;
		case SideWalking:
			if (model.GetSequence() != sideWalkNum)
			{
				model.SetSequence(sideWalkNum);
			}
			break;
		case Attacking:
			if (model.GetSequence() != attackNum)
			{
				model.SetSequence(attackNum);
			}
			break;
		default:
			if (model.GetSequence() != idleNum)
			{
				model.SetSequence(idleNum);
			}
			break;
		}
	}
}