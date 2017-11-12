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
	GLfloat i, j;

	GLfloat dimension = 50;
	GLfloat step = 1;

	// Checkered floor [testing]
	GLfloat colors[2][3] = { { 0.5f,0.5f,0.5f },
							{ 0.55f,0.55f,0.55f } };
	int swap = 1;

	for (i = -dimension; i <= dimension; i += step)
		for (j = -dimension; j <= dimension; j += step)
		{
			swap = (swap == 0) ? 1 : 0;
			glColor3fv(colors[swap]);
			glBegin(GL_POLYGON);
			glNormal3f(0, 0, 1);
			glVertex3f(i + step, j + step, 0);
			glVertex3f(i, j + step, 0);
			glVertex3f(i, j, 0);
			glVertex3f(i + step, j, 0);
			glEnd();
		}
}