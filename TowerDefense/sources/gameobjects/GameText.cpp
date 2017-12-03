#include "../../headers/gameobjects/GameText.h"
#include "../../headers/components/Transform.h"
#include "../../headers/util/Illumination.h"



GameText::GameText()
{
	addComponent("transform", new Transform());
	GLfloat color[3] = { 1.0, 1.0, 1.0 };
}

GameText::GameText(char * text)
{
	addComponent("transform", new Transform());
	this->text = text;
	GLfloat whitecolor[3] = { 1.0, 1.0, 1.0 };
	setColor(whitecolor);
}

GameText::~GameText()
{
}

void GameText::writeText() {

	int len = (int)strlen(text);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
		//glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
}

void GameText::draw()
{
	
	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Illumination::NO_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SHININESS, Illumination::NO_SHININESS);
	glMaterialfv(GL_FRONT, GL_EMISSION, Illumination::NO_MATERIAL);

	glRasterPos2f(t->position->x, t->position->y);

	writeText();

	glPopMatrix();
}


void GameText::setColor(GLfloat colorC[3])
{
	int i;
	for (i = 0; i < 3; i++) {
		color[i] = colorC[i];
	}
}