#include <stdlib.h>
#include <GL/glut.h>
#include "../../headers/scenes/Game.h"
#include "../../headers/framework/Application.h"
#include "../../headers/gameobjects/Camera.h"
#include "../../headers/gameobjects/Player.h"
#include "../../headers/gameobjects/Ground.h"
#include "../../headers/components/Transform.h"

Game::Game()
{
	Camera * c = new Camera();
	Transform * trans = (Transform*)c->getComponentById("transform");
	trans->position->x = 40;
	trans->position->y = 40;
	trans->position->z = 40;
	gameObjects["camera"] = c;

	Player * p = new Player();
	gameObjects["player"] = p;

	Ground * g = new Ground();
	gameObjects["ground"] = g;
}

void Game::Init()
{
	glClearColor(0.8, 0.3, 0.3, 0.0);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glutPostRedisplay();
}

void Game::Reshape(int width, int height)
{
	GLint size;
	GLfloat ratio = (GLfloat)width / height;
	GLfloat ratio1 = (GLfloat)height / width;

	if (width < height)
		size = width;
	else
		size = height;

	// glViewport(botom, left, width, height)
	// define the part of the window to be used by OpenGL

	//glViewport(0, 0, (GLint) size, (GLint) size);
	glViewport(0, 0, width, height);


	// The projection matrix
	// Matriz onde se define como o mundo e apresentado na janela
	// Matrix where you define how the world is shown in the window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	switch (Application::instance()->getState()->getCameraType())
	{
	case State::CameraType::ORTHO:
		if (width < height)
		{
			glOrtho(-20, 20, -20 * (GLdouble)height / width, 20 * (GLdouble)height / width, -100, 100);
		}
		else
		{
			glOrtho(-20 * (GLdouble)width / height, 20 * (GLdouble)width / height, -20, 20, -100, 100);
		}
		break;

	case State::CameraType::PERSPECTIVE:
		gluPerspective(((Camera*)gameObjects["camera"])->fieldOfView, (GLfloat)width / height, 1, 100);
		break;
	}

	// Matrix Modelview
	// Matrix where the designed models transforms are made
	glMatrixMode(GL_MODELVIEW);
}

void Game::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	gluLookAt(0, 5, 0.5, 0, 0, 0, 0, 0, 1);
	glTranslatef(0, -5, -0.5);

	((Ground*)gameObjects["ground"])->draw();

	((Player*)gameObjects["player"])->draw();

	glFlush();
	if (Application::instance()->getState()->isDoubleBufferActivated())
		glutSwapBuffers();
}

void Game::Timer(int value)
{
	// FIXME remove this, just for demonstration purposes
	Transform * playerT = (Transform*) ((Player*)gameObjects["player"])->getComponentById("transform");

	if (Application::instance()->getState()->getInputs()->move_front)
	{
		playerT->position->y -= 0.1;
	}
	if (Application::instance()->getState()->getInputs()->move_back)
	{
		playerT->position->y += 0.1;
	}
	if (Application::instance()->getState()->getInputs()->move_left)
	{
		playerT->position->x += 0.1;
	}
	if (Application::instance()->getState()->getInputs()->move_right)
	{
		playerT->position->x -= 0.1;
	}
}

void Game::Key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
		Application::instance()->getState()->getInputs()->move_front = true;
		break;
	case 's':
	case 'S':
		Application::instance()->getState()->getInputs()->move_back = true;
		break;
	case 'a':
	case 'A':
		Application::instance()->getState()->getInputs()->move_left = true;
		break;
	case 'd':
	case 'D':
		Application::instance()->getState()->getInputs()->move_right = true;
		break;
	}
}

void Game::KeyUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
		Application::instance()->getState()->getInputs()->move_front = false;
		break;
	case 's':
	case 'S':
		Application::instance()->getState()->getInputs()->move_back = false;
		break;
	case 'a':
	case 'A':
		Application::instance()->getState()->getInputs()->move_left = false;
		break;
	case 'd':
	case 'D':
		Application::instance()->getState()->getInputs()->move_right = false;
		break;
	}
}

void Game::SpecialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		Application::instance()->getSceneManager()->changeScene("menu");
		break;
	}
}

void Game::SpecialKeyUp(int key, int x, int y)
{

}