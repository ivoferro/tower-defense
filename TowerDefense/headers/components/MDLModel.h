#pragma once

#include <GL/glut.h>
#include "../../headers/mdlloader/Mdlloader.h"

enum States {Walking, SideWalking, Attacking, Death, Idle};

class MDLModel
{
public:
	GLboolean isInit;
	States state;
	GLuint prevSequence;
	StudioModel model;

	int idleNum;
	int walkNum;
	int sideWalkNum;
	int attackNum;
	int deathNum;
	int deadNum;
	char *file;

	void idle();
	void walk();
	void sideWalk();
	void attack(GLuint time);
	void death(GLuint time);
	void dead();
	void animate();

	GLboolean shooting;
	GLboolean stillShooting(GLuint time, GLuint frameSize);

	GLboolean dying;
	GLboolean stillDying(GLuint time, GLuint frameSize);

	void init();
	void draw();

	MDLModel(int idle, int walk, int sideWalk, int attack, int death, int dead, char *filename);
	~MDLModel();

private:

	GLuint startedShooting;
	GLuint startedDying;
};