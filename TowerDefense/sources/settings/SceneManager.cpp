#include "SceneManager.h"
#include "../scenes/Menu.h"
#include "../scenes/Game.h"

SceneManager::SceneManager()
{
	scenes["menu"] = new Menu();
	scenes["game"] = new Game();

	activeSceneKey = "menu";
}

IScene * SceneManager::activeScene()
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