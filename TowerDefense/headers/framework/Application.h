#pragma once

#include "State.h"
#include "SceneManager.h"
#include "Textures.h"
#include "Debugger.h"

class Application
{

private:
	Application();
	~Application();

	static Application *s_instance;

	State *state;
	SceneManager *sceneManager;
	Textures *textures;
	Debugger *debugger;

public:

	static Application *instance();

	State *getState();
	SceneManager *getSceneManager();
	Textures *getTextures();
	Debugger *getDebugger();
};

