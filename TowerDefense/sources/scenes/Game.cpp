#include <stdlib.h>
#include <GL/glut.h>
#include "../../headers/scenes/Game.h"
#include "../../headers/framework/Application.h"
#include "../../headers/gameobjects/Camera.h"
#include "../../headers/components/Transform.h"

Game::Game()
{
	Camera * cam = new Camera();
	Transform * trans = (Transform*)cam->getComponentById("transform");
	trans->position->x = 40;
	trans->position->y = 40;
	trans->position->z = 40;
	gameObjects["camera"] = cam;
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
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(-1, 1, 0);
	glVertex3f(-1, -1, 0);
	glVertex3f(1, -1, 0);
	glEnd();

	// Some placeholder text for texting purposes
	glColor3f(0, 0, 1);
	char str[] = "Second Scene! Press F1 to switch to first scene!";
	glRasterPos2f(-1, -0.7);
	int len = (int)strlen(str);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}

	glFlush();
	if (Application::instance()->getState()->isDoubleBufferActivated())
		glutSwapBuffers();
}

void Game::Timer(int value)
{

}

void Game::Key(unsigned char key, int x, int y)
{

}

void Game::KeyUp(unsigned char key, int x, int y)
{

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