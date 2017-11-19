#pragma once

#include "State.h"
#include "SceneManager.h"
#include "Textures.h"

class Application
{

private:
	Application();
	~Application();

	static Application *s_instance;

	State *state;
	SceneManager *sceneManager;
	Textures *textures;

public:

	static Application *instance();

	State *getState();
	SceneManager *getSceneManager();
	Textures *getTextures();
};

