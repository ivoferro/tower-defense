#include <stdlib.h>
#include <GL/glut.h>
#include "../../headers/scenes/Menu.h"
#include "../../headers/framework/Application.h"
#include "../../headers/components/Transform.h"
#include "../../headers/gameobjects/GameText.h"

Menu::Menu()
{
}

void Menu::Init()
{
	glClearColor(0.3, 0.3, 0.3, 0.0);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glutPostRedisplay();
}

void Menu::Reshape(int width, int height)
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

	// gluOrtho2D(left,right,bottom,top); 
	// 2D orthogonal projection, with a depth of (Z) between -1 and 1
	if (width < height)
		gluOrtho2D(-1, 1, -1 * ratio1, 1 * ratio1);
	else
		gluOrtho2D(-1 * ratio, 1 * ratio, -1, 1);

	// Matrix Modelview
	// Matrix where the designed models transforms are made
	glMatrixMode(GL_MODELVIEW);
}

void Menu::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
		glVertex3f(0.5, -0.5, -0.5);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(0.5, 0.5, -0.5);
	glEnd();

	// Some placeholder text for texting purposes
	GameText * gt1 = new GameText("TESTE");
	gameObjects["game_text"] = gt1;

	Transform * trans = (Transform*)gt1->getComponentById("transform");
	trans->position->x = 40;
	trans->position->y = 40;
	trans->position->z = 40;

	gt1->DrawText();

	glFlush();
	if (Application::instance()->getState()->isDoubleBufferActivated())
		glutSwapBuffers();
}

void Menu::Timer(int value)
{

}

void Menu::Key(unsigned char key, int x, int y)
{

}

void Menu::KeyUp(unsigned char key, int x, int y)
{

}

void Menu::SpecialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F2:
		Application::instance()->getSceneManager()->changeScene("game");
		break;
	}
}

void Menu::SpecialKeyUp(int key, int x, int y)
{
}

void Menu::Mouse(int button, int mouse_state, int x, int y)
{

}

void Menu::MouseMotion(int x, int y)
{

}

void Menu::MousePassiveMotion(int x, int y)
{

}