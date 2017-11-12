#include "../../headers/gameobjects/GameText.h"
#include "../../headers/components/Transform.h"

GameText::GameText()
{
	addComponent("transform", new Transform());
}

GameText::GameText(char* theText)
{
	text = theText;
	addComponent("transform", new Transform());
}

void GameText::DrawText()
{
	Transform * t = (Transform*)getComponentById("transform");

	// Some placeholder text for texting purposes
	glColor3f(0, 1, 0);

	glRasterPos2f(-1, -0.7);
	int len = (int)strlen(text);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
}