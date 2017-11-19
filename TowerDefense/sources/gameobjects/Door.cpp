#include "../../headers/gameobjects/Door.h"
#include "../../headers/components/Transform.h"

Door::Door()
{
	addComponent("transform", new Transform());
}

Door::~Door()
{
}

void Door::draw()
{
	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();
		glTranslatef(t->position->x, t->position->y, t->position->z);
		glRotatef(t->rotation->z, 0, 0, 1);

		glPushMatrix();
			glTranslatef(1, 0, 0);
			glScalef(.5, .5, 3);
			drawCube();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1, 0, 0);
			glScalef(.5, .5, 3);
			drawCube();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0, 1.5);
		glScalef(2.5, .5, .5);
		drawCube();
		glPopMatrix();

	glPopMatrix();
}

void Door::drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat cor[])
{
	glBegin(GL_POLYGON);
	glColor3fv(cor);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();
}

void Door::drawCube()
{
	GLfloat vertices[][3] = {
		{ 0.5,  0.5,  0.5 },
		{ -0.5,  0.5,  0.5 },
		{ -0.5,  0.5, -0.5 },
		{ 0.5,  0.5, -0.5 },
		{ 0.5, -0.5,  0.5 },
		{ -0.5, -0.5,  0.5 },
		{ -0.5, -0.5, -0.5 },
		{ 0.5, -0.5, -0.5 } };

	GLfloat colors[][3] = {
		{ 0.5, 0.0, 0.0 },
		{ 0.0, 0.5, 0.0 },
		{ 0.0, 0.0, 0.5 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 0.0, 1.0 } };

	drawPolygon(vertices[0], vertices[3], vertices[2], vertices[1], colors[0]);
	drawPolygon(vertices[1], vertices[2], vertices[6], vertices[5], colors[1]);
	drawPolygon(vertices[5], vertices[6], vertices[7], vertices[4], colors[2]);
	drawPolygon(vertices[4], vertices[7], vertices[3], vertices[0], colors[3]);
	drawPolygon(vertices[1], vertices[5], vertices[4], vertices[0], colors[4]);
	drawPolygon(vertices[2], vertices[3], vertices[7], vertices[6], colors[5]);
}