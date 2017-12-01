#pragma once

#include <GL/glut.h>
#include "../../headers/mdlloader/Mdlloader.h"

enum States {Walking, SideWalking, Attacking, Idle};

class MDLModel
{
public:
	GLboolean isInit;
	GLboolean isWalking;
	States state;
	GLuint prevSequence;
	StudioModel model;

	void idle();
	void walk();
	void sideWalk();
	void attack();

	MDLModel();
	~MDLModel();

private:

};