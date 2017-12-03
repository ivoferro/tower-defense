#pragma once

#include <map>
#include "Scene.h"

class SceneManager
{
	
private:
	std::map<std::string, Scene*> scenes;
	std::string activeSceneKey;

public:
	SceneManager();
	~SceneManager();

	Scene * activeScene();
	void changeScene(std::string sceneKey);
	void SceneManager::restartScene(std::string sceneKey);

};