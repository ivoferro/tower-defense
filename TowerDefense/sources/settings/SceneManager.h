#pragma once

#include <map>
#include "../scenes/IScene.h"

class SceneManager
{
	
private:
	std::map<std::string, IScene*> scenes;
	std::string activeSceneKey;

public:
	SceneManager();

	IScene * activeScene();
	void changeScene(std::string sceneKey);

};