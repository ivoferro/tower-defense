#include "../../headers/gameobjects/GameText.h"
#include "../../headers/components/Transform.h"

GameText::GameText()
{
	addComponent("transform", new Transform());
}

GameText::~GameText()
{
}

void GameText::drawText(char * text)
{
	
	Transform * t = (Transform*)getComponentById("transform");
	glRasterPos2f(t->position->x, t->position->y);
	// Some placeholder text for texting purposes
	glColor3f(0, 1, 0);

	int len = (int)strlen(text);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
}