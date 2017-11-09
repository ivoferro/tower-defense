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

public:
	GameObject();
	~GameObject();

	GLboolean addComponent(std::string id, Component *aComponent);
	Component * getComponentById(std::string id);
	std::list<Component*> getComponentsByTag(std::string tag);

};