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

GLboolean GameObject::addTag(std::string tag)
{
	if (hasTag(tag))
	{
		return false;
	}

	tags.push_back(tag);
	return true;
}

GLboolean GameObject::hasTag(std::string tag)
{
	return std::find(tags.begin(), tags.end(), tag) != tags.end();
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

GLboolean GameObject::removeComponent(std::string id)
{
	if (hasComponent(id)) {
		components.erase(id);
		return true;
	}
	return false;
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
