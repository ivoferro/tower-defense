#pragma once

#include <map>
#include "GameObject.h"

class Scene
{

protected:
	std::map<std::string, GameObject *> gameObjects;

public:
	Scene();
	~Scene();

	virtual void Init() = 0;
	virtual void Reshape(int width, int height) = 0;
	virtual void Draw() = 0;
	virtual void Timer(int value) = 0;
	virtual void Key(unsigned char key, int x, int y) = 0;
	virtual void KeyUp(unsigned char key, int x, int y) = 0;
	virtual void SpecialKey(int key, int x, int y) = 0;
	virtual void SpecialKeyUp(int key, int x, int y) = 0;
	virtual void Mouse(int button, int mouse_state, int x, int y) = 0;
	virtual void MouseMotion(int x, int y) = 0;
	virtual void MousePassiveMotion(int x, int y) = 0;

};