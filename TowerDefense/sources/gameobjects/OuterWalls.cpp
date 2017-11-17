#include "../../headers/gameobjects/OuterWalls.h"
#include "../../headers/components/Transform.h"
#include "../../headers/util/Illumination.h"

OuterWalls::OuterWalls()
{
	addComponent("transform", new Transform());
}

OuterWalls::~OuterWalls()
{
}

void OuterWalls::draw()
{
	drawWalls(50, 22);
	
	GLfloat doorColor[3] = { 0,0,0 };
	//drawDoor(doorColor);
}

void OuterWalls::drawWalls(GLfloat width, GLfloat height)
{
	GLfloat i, j;
	GLfloat step = 1;

	GLfloat colors1[2][3] = { { 0.3f,0.5f,0.5f },
	{ 0.3f,0.6f,0.6f } };
	GLfloat colors2[2][3] = { { 0.3f,0.2f,0.2f },
	{ 0.2f,0.3f,0.3f } };
	int swap = 1;

	for (i = -width; i <= width; i += step)
		for (j = 0; j <= height; j += step)
		{
			swap = (swap == 0) ? 1 : 0;
			glMaterialfv(GL_FRONT, GL_AMBIENT, colors1[swap]);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, colors1[swap]);
			glMaterialfv(GL_FRONT, GL_SPECULAR, Illumination::NO_MATERIAL);
			glMaterialfv(GL_FRONT, GL_SHININESS, Illumination::NO_SHININESS);
			glMaterialfv(GL_FRONT, GL_EMISSION, Illumination::NO_MATERIAL);

			// Wall 1
			glBegin(GL_POLYGON);
			glNormal3f(-1, 0, 0);
			glVertex3f(-50, i + step, j + step);
			glVertex3f(-50, i, j + step);
			glVertex3f(-50, i, j);
			glVertex3f(-50, i + step, j);
			glEnd();

			// Wall 2
			glBegin(GL_POLYGON);
			glNormal3f(1, 0, 0);
			glVertex3f(51, i + step, j + step);
			glVertex3f(51, i, j + step);
			glVertex3f(51, i, j);
			glVertex3f(51, i + step, j);
			glEnd();

			glMaterialfv(GL_FRONT, GL_AMBIENT, colors2[swap]);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, colors2[swap]);
			// Wall 3
			glBegin(GL_POLYGON);
			glNormal3f(0, -1, 0);
			glVertex3f(i + step, -50, j + step);
			glVertex3f(i, -50, j + step);
			glVertex3f(i, -50, j);
			glVertex3f(i + step, -50, j);
			glEnd();

			// Wall 4
			glBegin(GL_POLYGON);
			glNormal3f(0, 1, 0);
			glVertex3f(i + step, 51, j + step);
			glVertex3f(i, 51, j + step);
			glVertex3f(i, 51, j);
			glVertex3f(i + step, 51, j);
			glEnd();
		}
}

void OuterWalls::drawDoor(GLfloat color[3])
{
	glBegin(GL_POLYGON);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glVertex3f(1.0f,0,0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1.0f, 0);
	glVertex3f(0, -1.0f, 0);
	glEnd();
}