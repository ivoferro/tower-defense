#pragma once

#include "../framework/GameObject.h"
#include <map>

class GameText : public GameObject
{

private:
	char* text;
	GLfloat color[3];
	void writeText();

public:
	GameText();
	GameText(char* text);
	~GameText();

	void drawText();
	void setColor(GLfloat color[3]);
};
