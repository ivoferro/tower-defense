#include "../../headers/framework/Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (std::map<std::string, GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		it->second->~GameObject();
	}
}