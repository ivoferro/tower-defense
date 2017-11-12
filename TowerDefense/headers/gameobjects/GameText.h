#pragma once

#include "../framework/GameObject.h"
#include <map>

class GameText : public GameObject
{

public:
	GameText();
	GameText(char* text);
	~GameText();

	char* text;

	void DrawText();
};