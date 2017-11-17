#pragma once

#include "../framework/Scene.h"

class Game : public Scene
{

private:
	void MouseMovement(int x, int y);
	void detectCollisions();
	void moveCamera();
	void setLight();

public:
	Game();
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