#pragma once

#include "../framework/Scene.h"

class Menu : public Scene
{

private:
	void setLight();
	void setSelection(int x, int y);
	void setTextures();
	void createGameObjects();
	void drawGameObjects();
	void dragOptions(GLfloat pos);
	void clearText();
	void startGame();
	void help();
	void credits();
	int width, height, id;
	GLdouble coordBars[5][3];

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
	void Mouse(int button, int mouse_state, int x, int y);
	void MouseMotion(int x, int y);
	void MousePassiveMotion(int x, int y);
};