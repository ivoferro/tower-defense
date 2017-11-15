#include "../../headers/gameobjects/MenuBar.h"
#include "../../headers/components/Transform.h"

MenuBar::MenuBar()
{
	addComponent("transform", new Transform());
}


MenuBar::~MenuBar()
{
}

void MenuBar::drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat cor[])
{
	/* draw a polygon via list of vertices */

	glBegin(GL_POLYGON);
	glColor3fv(cor);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();
}

void MenuBar::drawBar()
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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void MenuBar::draw()
{
	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();
	glTranslatef(t->position->x, t->position->y, t->position->z);
	glScalef(0.7,0.3,0.5);

	//FIXME Transparency
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	drawBar();
	glPopMatrix();
}

void MenuBar::changeColor() {
	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();
	glTranslatef(t->position->x, t->position->y, t->position->z);
	glScalef(0.7, 0.3, 0.5);

	//FIXME Transparency
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	drawBarOver();
	glPopMatrix();
}


void MenuBar::drawBarOver()
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
		{ 1, 0.0, 0.0 },
		{ 1, 0.5, 0.0 },
		{ 0.0, 0.0, 0.5 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 1.0 },
		{ 1.0, 0.0, 1.0 } };

	drawPolygon(vertices[0], vertices[3], vertices[2], vertices[1], colors[0]);
	drawPolygon(vertices[1], vertices[2], vertices[6], vertices[5], colors[1]);
	drawPolygon(vertices[5], vertices[6], vertices[7], vertices[4], colors[2]);
	drawPolygon(vertices[4], vertices[7], vertices[3], vertices[0], colors[3]);
	drawPolygon(vertices[1], vertices[5], vertices[4], vertices[0], colors[4]);
	drawPolygon(vertices[2], vertices[3], vertices[7], vertices[6], colors[5]);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}