#pragma once

#include "IScene.h"

class Menu : public IScene
{

public:
	Menu();
	void Init();
	void Reshape(int width, int height);
	void Draw();
	void Timer(int value);
	void Key(unsigned char key, int x, int y);
	void KeyUp(unsigned char key, int x, int y);
	void SpecialKey(int key, int x, int y);
	void SpecialKeyUp(int key, int x, int y);

};