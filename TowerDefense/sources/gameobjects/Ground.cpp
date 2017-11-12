#include "../../headers/gameobjects/Ground.h"
#include "../../headers/components/Transform.h"

Ground::Ground()
{
	addComponent("transform", new Transform());
}

Ground::~Ground()
{
}

void Ground::draw()
{
	GLfloat dimension = 5;
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f(0.3, 0.3, 0.3, 1);
	glVertex3f(dimension, dimension, 0);
	glVertex3f(-dimension, dimension, 0);
	glVertex3f(-dimension, -dimension, 0);
	glVertex3f(dimension, -dimension, 0);
	glEnd();
	glPopMatrix();
}