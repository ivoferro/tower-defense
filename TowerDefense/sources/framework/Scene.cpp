#include "../../headers/framework/Scene.h"
#include <string>

std::string Scene::generateKey()
{
	return "_gen_key_" + std::to_string(idGenerator++);
}

Scene::Scene()
{
	idGenerator = 0;
}

Scene::~Scene()
{
	for (std::map<std::string, GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		it->second->~GameObject();
	}
}

GLboolean Scene::hasGameObject(std::string id)
{
	return (gameObjects.find(id) != gameObjects.end());
}

GLboolean Scene::hasGameObject(GameObject * gameObject)
{
	for (std::map<std::string, GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		if ((it->second) == gameObject)
		{
			return true;
		}
	}
	return false;
}

GLboolean Scene::addGameObject(std::string id, GameObject * gameObject)
{
	if (hasGameObject(id)) {
		return false;
	}

	gameObjects[id] = gameObject;
	return true;
}

GLboolean Scene::addGameObject(GameObject * gameObject)
{
	if (hasGameObject(gameObject))
	{
		return false;
	}

	std::string genID = generateKey();

	gameObjects[genID] = gameObject;
	return true;
}

GLboolean Scene::removeGameObject(std::string id)
{
	if (!hasGameObject(id))
	{
		return false;
	}
	gameObjects.erase(id);
	return true;
}

GLboolean Scene::removeGameObject(GameObject * gameObject)
{
	for (std::map<std::string, GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		if ((it->second) == gameObject)
		{
			gameObjects.erase(it);
			return true;
		}
	}
	return false;
}

std::string Scene::addToWaitingObjects(GameObject * gameObject)
{
	std::string genKey = generateKey();
	waitingGameObjects[genKey] = gameObject;
	return genKey;
}

GLboolean Scene::activateObject(std::string objectKey)
{
	std::map<std::string, GameObject *>::iterator it = waitingGameObjects.find(objectKey);
	if (it != waitingGameObjects.end() && !hasGameObject(it->first))
	{
		addGameObject(it->first, it->second);
		waitingGameObjects.erase(it->first);
		return true;
	}
	return false;
}