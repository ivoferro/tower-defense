#include "../../headers/gameobjects/Ground.h"
#include "../../headers/components/Transform.h"
#include "../../headers/util/Illumination.h"

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

			glBegin(GL_POLYGON);

			glMaterialfv(GL_FRONT, GL_AMBIENT, colors[swap]);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[swap]);
			glMaterialfv(GL_FRONT, GL_SPECULAR, Illumination::NO_MATERIAL);
			glMaterialfv(GL_FRONT, GL_SHININESS, Illumination::NO_SHININESS);
			glMaterialfv(GL_FRONT, GL_EMISSION, Illumination::NO_MATERIAL);

			glNormal3f(0, 0, 1);
			glVertex3f(i + step, j + step, 0);
			glVertex3f(i, j + step, 0);
			glVertex3f(i, j, 0);
			glVertex3f(i + step, j, 0);
			glEnd();
		}
}