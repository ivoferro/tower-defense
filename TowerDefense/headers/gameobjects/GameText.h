#pragma once

#include "../framework/GameObject.h"
#include <map>

class GameText : public GameObject
{

private:
	char* text;
	void writeText();

public:
	GameText();
	GameText(char* text);
	~GameText();

	void drawText();
	void changeColor();
};
