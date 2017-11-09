#include "../../headers/framework/SceneManager.h"
#include "../../headers/scenes/Menu.h"
#include "../../headers/scenes/Game.h"

SceneManager::SceneManager()
{
	scenes["menu"] = new Menu();
	scenes["game"] = new Game();

	activeSceneKey = "menu";
}

SceneManager::~SceneManager()
{
	for (std::map<std::string, Scene*>::iterator it = scenes.begin(); it != scenes.end(); ++it)
	{
		it->second->~Scene();
	}
}

Scene * SceneManager::activeScene()
{
	return scenes[activeSceneKey];
}

void SceneManager::changeScene(std::string sceneKey)
{
	if (scenes.find(sceneKey) != scenes.end())
	{
		scenes[sceneKey]->Init();
		activeSceneKey = sceneKey;
	}
}