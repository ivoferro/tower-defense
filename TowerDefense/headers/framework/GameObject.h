#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include <map>
#include <list>
#include "Component.h"

class GameObject
{

private:
	std::map<std::string, Component*> components;
	std::list<std::string> tags;

public:
	GameObject();
	~GameObject();

	GLboolean addTag(std::string tag);
	GLboolean hasTag(std::string tag);

	GLboolean hasComponent(std::string id);
	GLboolean addComponent(std::string id, Component *aComponent);
	Component * getComponentById(std::string id);
	GLboolean removeComponent(std::string id);
	std::list<Component*> getComponentsByTag(std::string tag);
	virtual void onCollisionEnter(GameObject * collidingObject);
	virtual void draw();

};