#pragma once

#include <map>
#include "GameObject.h"

class Scene
{

private:
	unsigned int idGenerator;
	std::string generateKey();

protected:
	std::map<std::string, GameObject *> gameObjects;
	std::map<std::string, GameObject *> waitingGameObjects;

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

	GLboolean hasGameObject(std::string id);
	GLboolean hasGameObject(GameObject * gameObject);

	GLboolean addGameObject(std::string id, GameObject * gameObject);
	GLboolean addGameObject(GameObject * gameObject);

	GLboolean removeGameObject(std::string id);
	GLboolean removeGameObject(GameObject * gameObject);

	std::string addToWaitingObjects(GameObject * gameObject);
	GLboolean activateObject(std::string objectKey);

};