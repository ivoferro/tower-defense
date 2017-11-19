#include "../../headers/framework/Application.h"

Application *Application::s_instance = 0;

Application::Application()
{
	state = new State();
	sceneManager = new SceneManager();
	textures = new Textures();
}

Application::~Application()
{
	state->~State();
	sceneManager->~SceneManager();
}

Application * Application::instance()
{
	if (!s_instance) {
		s_instance = new Application();
	}
	return s_instance;
}

State * Application::getState()
{
	return state;
}

SceneManager * Application::getSceneManager()
{
	return sceneManager;
}

Textures * Application::getTextures()
{
	return textures;
}