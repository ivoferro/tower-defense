#include "../../headers/gameobjects/MenuBar.h"
#include "../../headers/components/Transform.h"
#include "../../headers/framework/Application.h"

MenuBar::MenuBar()
{
	addComponent("transform", new Transform());
	this->width = 0.4f;
	this->height = 0.15f;
}


MenuBar::~MenuBar()
{
}

void MenuBar::drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat colors[])
{
	/* draw a polygon via list of vertices */

	Transform* t = (Transform*)getComponentById("transform");

	glBindTexture(GL_TEXTURE_2D, Application::instance()->getTextures()->getTexture("vinil"));

	glBegin(GL_POLYGON);

	glNormal3fv(colors);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2fv(b);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2fv(a);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2fv(c);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2fv(d);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void MenuBar::drawBar()
{
	GLfloat vertices[][2] = {
		{ width,  -height },
		{ -width,  -height },
		{ width,  height },
		{ -width,  height }
	};

	GLfloat colors[][3] ={ 1,  1,  1 };

	drawPolygon(vertices[0], vertices[1], vertices[2], vertices[3], colors[0]);
}

void MenuBar::draw()
{
	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();
	glTranslatef(t->position->x, t->position->y, t->position->z);
	glScalef(t->scale->x, t->scale->y, t->scale->z);

	drawBar();
	glPopMatrix();
}

void MenuBar::changeColor() {
	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();
	glTranslatef(t->position->x, t->position->y, t->position->z);
	glScalef(t->scale->x, t->scale->y, t->scale->z);

	drawBarOver();
	glPopMatrix();
}


void MenuBar::drawBarOver()
{
	GLfloat vertices[][2] = {
		{ 0.4f,  -0.15f },
		{ -0.4f,  -0.15f },
		{ 0.4f,  0.15f },
		{ -0.4f,  0.15f }
	};

	GLfloat colors[][3] = { 01,  0,  0 };

	drawPolygonOver(vertices[0], vertices[1], vertices[2], vertices[3], colors[0]);
}

GLfloat MenuBar::getWidth() {
	return width;
}

GLfloat MenuBar::getHeight() {
	return height;
}


void MenuBar::drawPolygonOver(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat colors[])
{
	/* draw a polygon via list of vertices */

	Transform* t = (Transform*)getComponentById("transform");

	glBindTexture(GL_TEXTURE_2D, Application::instance()->getTextures()->getTexture("vinil"));

	glBegin(GL_POLYGON);

	glNormal3fv(colors);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2fv(b);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2fv(a);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2fv(c);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2fv(d);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);
}