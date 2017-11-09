#pragma once

#include "State.h"
#include "SceneManager.h"

class Application
{

private:
	Application();
	~Application();

	static Application *s_instance;

	State *state;
	SceneManager *sceneManager;

public:

	static Application *instance();

	State *getState();
	SceneManager *getSceneManager();
};

