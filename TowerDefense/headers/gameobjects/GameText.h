#pragma once

#include "../framework/GameObject.h"
#include "../framework/Drawable.h"
#include <map>

class GameText : public GameObject, Drawable
{

private:
	char* text;
	GLfloat color[3];
	void writeText();

public:
	GameText();
	GameText(char* text);
	~GameText();

	void draw();
	void setColor(GLfloat color[3]);
};