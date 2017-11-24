#include "../../headers/gameobjects/GameText.h"
#include "../../headers/components/Transform.h"
#include "../../headers/util/Illumination.h"

GameText::GameText()
{
	addComponent("transform", new Transform());
}

GameText::GameText(char * text)
{
	addComponent("transform", new Transform());
	this->text = text;
}

GameText::~GameText()
{
}

void GameText::writeText() {

	int len = (int)strlen(text);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
}

void GameText::drawText()
{
	GLfloat blackcolor[3] = { 1.0, 1.0, 1.0 };
	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, blackcolor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blackcolor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Illumination::NO_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SHININESS, Illumination::NO_SHININESS);
	glMaterialfv(GL_FRONT, GL_EMISSION, Illumination::NO_MATERIAL);

	glRasterPos2f(t->position->x, t->position->y);

	writeText();

	glPopMatrix();
}

void GameText::changeColor()
{

	GLfloat whitecolor[3] = { 0.0, 0.0, 0.0 };
	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, whitecolor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, whitecolor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Illumination::NO_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SHININESS, Illumination::NO_SHININESS);
	glMaterialfv(GL_FRONT, GL_EMISSION, Illumination::NO_MATERIAL);

	glRasterPos2f(t->position->x, t->position->y);

	writeText();

	glPopMatrix();
}