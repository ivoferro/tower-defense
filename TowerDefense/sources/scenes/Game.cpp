#include <stdlib.h>
#include <GL/glut.h>
#include "../../headers/scenes/Game.h"
#include "../../headers/framework/Application.h"
#include "../../headers/util/Math.h"
#include "../../headers/gameobjects/Camera.h"
#include "../../headers/gameobjects/Enemy.h"
#include "../../headers/gameobjects/Player.h"
#include "../../headers/gameobjects/Ground.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/CharacterPhysics.h"
#include "../../headers/components/CameraSettings.h"

Game::Game()
{
	Camera * c = new Camera();
	gameObjects["camera"] = c;

	Player * p = new Player();
	gameObjects["player"] = p;

	Ground * g = new Ground();
	gameObjects["ground"] = g;

	Enemy *e1 = new Enemy();
	gameObjects["enemy1"] = e1;
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

	CameraSettings * camSettings = (CameraSettings*)((Camera*)gameObjects["camera"])->getComponentById("settings");

	switch (camSettings->cameraType)
	{
	case CameraSettings::CameraType::ORTHO:
		if (width < height)
		{
			glOrtho(-20, 20, -20 * (GLdouble)height / width, 20 * (GLdouble)height / width, -100, 100);
		}
		else
		{
			glOrtho(-20 * (GLdouble)width / height, 20 * (GLdouble)width / height, -20, 20, -100, 100);
		}
		break;

	case CameraSettings::CameraType::PERSPECTIVE:
		gluPerspective(camSettings->fieldOfView, (GLfloat)width / height, 1, 100);
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

	Transform * cameraT = (Transform*)((Camera*)gameObjects["camera"])->getComponentById("transform");
	Transform * playerT = (Transform*)((Player*)gameObjects["player"])->getComponentById("transform");
	
	gluLookAt(
		cameraT->position->x, cameraT->position->y, cameraT->position->z,
		playerT->position->x, playerT->position->y, playerT->position->z, 
		0, 0, 1);

	((Ground*)gameObjects["ground"])->draw();

	((Player*)gameObjects["player"])->draw();

	// draw of enemy1
	glPushMatrix();
	glTranslatef(-10, -10, -0.5);
	glColor3f(0.5f, 0.5f, 0.5f);
	((Enemy*)gameObjects["enemy1"])->draw();
	glPopMatrix();

	glFlush();
	if (Application::instance()->getState()->isDoubleBufferActivated())
		glutSwapBuffers();
}

void Game::Timer(int value)
{
	Transform * cameraT = (Transform*)((Camera*)gameObjects["camera"])->getComponentById("transform");
	Transform * playerT = (Transform*) ((Player*)gameObjects["player"])->getComponentById("transform");
	CharacterPhysics * playerPhy = (CharacterPhysics*)((Player*)gameObjects["player"])->getComponentById("physics");
	CameraSettings * camSettings = (CameraSettings*)((Camera*)gameObjects["camera"])->getComponentById("settings");

	if (Application::instance()->getState()->getInputs()->zoom_in)
	{
		if (camSettings->distanceFromTarget > camSettings->minDistanceFromTarget)
		{
			camSettings->distanceFromTarget -= 0.5;
		}
	}
	if (Application::instance()->getState()->getInputs()->zoom_out)
	{
		if (camSettings->distanceFromTarget < camSettings->maxDistanceFromTarget)
		{
			camSettings->distanceFromTarget += 0.5;
		}
	}

	// acelarations
	if (Application::instance()->getState()->getInputs()->move_player_front)
	{
		if (playerPhy->velocity < playerPhy->maxFrontVelocity)
		{
			playerPhy->velocity += 0.01;
		}
	}
	if (Application::instance()->getState()->getInputs()->move_player_back)
	{
		if (playerPhy->velocity > - playerPhy->maxBackVelocity)
		{
			playerPhy->velocity -= 0.01;
		}
	}
	if (!Application::instance()->getState()->getInputs()->move_player_front &&
		!Application::instance()->getState()->getInputs()->move_player_back)
	{
		playerPhy->velocity = 0;
	}

	// side movements
	if (Application::instance()->getState()->getInputs()->move_player_left)
	{
		if (playerPhy->sideVelocity < playerPhy->maxSideVelocity)
		{
			playerPhy->sideVelocity += 0.01;
		}
	}
	if (Application::instance()->getState()->getInputs()->move_player_right)
	{
		if (playerPhy->sideVelocity > - playerPhy->maxSideVelocity)
		{
			playerPhy->sideVelocity -= 0.01;
		}
	}
	if (!Application::instance()->getState()->getInputs()->move_player_left &&
		!Application::instance()->getState()->getInputs()->move_player_right)
	{
		playerPhy->sideVelocity = 0;
	}
	
	// changes player position according to front/back movements
	playerT->position->x += playerPhy->velocity * cos(Math::radians(playerT->rotation->z - 90));
	playerT->position->y += playerPhy->velocity * sin(Math::radians(playerT->rotation->z - 90));
	// changes player position according to side movements
	playerT->position->x += playerPhy->sideVelocity * cos(Math::radians(playerT->rotation->z));
	playerT->position->y += playerPhy->sideVelocity * sin(Math::radians(playerT->rotation->z));

	// changes camera position according to player
	cameraT->position->x = playerT->position->x + (camSettings->distanceFromTarget * cos(Math::radians(playerT->rotation->z + 90)) );
	cameraT->position->y = playerT->position->y + (camSettings->distanceFromTarget * sin(Math::radians(playerT->rotation->z + 90)) );
	cameraT->position->z = 0.5 + playerT->position->z;
}

void Game::Key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
		Application::instance()->getState()->getInputs()->move_player_front = true;
		break;
	case 's':
	case 'S':
		Application::instance()->getState()->getInputs()->move_player_back = true;
		break;
	case 'a':
	case 'A':
		Application::instance()->getState()->getInputs()->move_player_left = true;
		break;
	case 'd':
	case 'D':
		Application::instance()->getState()->getInputs()->move_player_right = true;
		break;
	case '1':
		Application::instance()->getState()->getInputs()->zoom_in = true;
		break;
	case '2':
		Application::instance()->getState()->getInputs()->zoom_out = true;
		break;
	}
}

void Game::KeyUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
		Application::instance()->getState()->getInputs()->move_player_front = false;
		break;
	case 's':
	case 'S':
		Application::instance()->getState()->getInputs()->move_player_back = false;
		break;
	case 'a':
	case 'A':
		Application::instance()->getState()->getInputs()->move_player_left = false;
		break;
	case 'd':
	case 'D':
		Application::instance()->getState()->getInputs()->move_player_right = false;
		break;
	case '1':
		Application::instance()->getState()->getInputs()->zoom_in = false;
		break;
	case '2':
		Application::instance()->getState()->getInputs()->zoom_out = false;
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

void Game::Mouse(int button, int mouse_state, int x, int y)
{
}

void Game::MouseMotion(int x, int y)
{
	MouseMovement(x, y);
}

void Game::MousePassiveMotion(int x, int y)
{
	MouseMovement(x, y);
}

void Game::MouseMovement(int x, int y)
{

	Transform * playerT = (Transform*)((Player*)gameObjects["player"])->getComponentById("transform");

	if (x > Application::instance()->getState()->mousePositionX)
	{
		// FIXME this logic should not be here, on the other hand there is not a
		// callback that triggers when mouse is not moving
		// Application::instance()->getState()->getInputs()->move_camera_left = true;
		playerT->rotation->z -= 1;
	}
	else if (x < Application::instance()->getState()->mousePositionX)
	{
		// FIXME this logic should not be here, on the other hand there is not a
		// callback that triggers when mouse is not moving
		// Application::instance()->getState()->getInputs()->move_camera_right = true;
		playerT->rotation->z += 1;
	}

	if (y > Application::instance()->getState()->mousePositionY)
	{
	}
	else if (y < Application::instance()->getState()->mousePositionY)
	{
	}

	// saves the last (x;y) positions to compare in the next call
	Application::instance()->getState()->mousePositionX = x;
	Application::instance()->getState()->mousePositionY = y;
}