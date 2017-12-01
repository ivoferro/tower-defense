#include "../../headers/framework/GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	for (std::map<std::string, Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		it->second->~Component();
	}
}

GLboolean GameObject::hasComponent(std::string id)
{
	return (components.find(id) != components.end());
}

GLboolean GameObject::addComponent(std::string id, Component * aComponent)
{
	if (hasComponent(id)) {
		return false;
	}

	components[id] = aComponent;
	return true;
}

Component * GameObject::getComponentById(std::string id)
{
	return components[id];
}

std::list<Component*> GameObject::getComponentsByTag(std::string tag)
{
	std::list<Component*> componentsWithTag;

	for (std::map<std::string, Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if (it->second->hasTag(tag))
		{
			componentsWithTag.push_front(it->second);
		}
	}

	return componentsWithTag;
}

void GameObject::onCollisionEnter(GameObject * collidingObject)
{
}

void GameObject::draw()
{
}
