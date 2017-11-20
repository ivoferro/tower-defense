#include <stdlib.h>
#include <GL/glut.h>
#include "../../headers/gameobjects/Camera.h"
#include "../../headers/scenes/Menu.h"
#include "../../headers/framework/Application.h"
#include "../../headers/components/Transform.h"
#include "../../headers/gameobjects/GameText.h"
#include "../../headers/gameobjects/Player.h"
#include "../../headers/gameobjects/Tower.h"
#include "../../headers/gameobjects/MenuBar.h"



Menu::Menu()
{
	int xBase = -1;
	int yBase = 0;

	Camera * c = new Camera();
	gameObjects["camera"] = c;

	MenuBar *mb = new MenuBar();
	Transform *mbT1 = (Transform*)mb->getComponentById("transform");
	mbT1->position->x = xBase;
	mbT1->position->y = yBase-0.5;
	mbT1->position->z =  0.5;

	gameObjects["menubar1"] = mb;

	MenuBar *mb2 = new MenuBar();
	Transform *mbT2 = (Transform*)mb2->getComponentById("transform");
	mbT2->position->x = xBase;
	mbT2->position->y = yBase;

	gameObjects["menubar2"] = mb2;

	MenuBar *mb3 = new MenuBar();
	Transform *mbT3 = (Transform*)mb3->getComponentById("transform");
	mbT3->position->x = xBase;
	mbT3->position->y = yBase+ 0.5;
	//	mbT->scale->x = -0.5;
	//mbT->scale->y = 0.5;
	gameObjects["menubar3"] = mb3;
	
	GameText * gtStart = new GameText();
	Transform *gtStartT = (Transform*)gtStart->getComponentById("transform");
	gtStartT->position->x = xBase+0.2;
	gtStartT->position->y = yBase+0.5;
	gameObjects["gametext"] = gtStart;

	GameText * gtCredits = new GameText();
	Transform *gtCreditsT = (Transform*)gtCredits->getComponentById("transform");
	gtCreditsT->position->x = xBase;
	gtCreditsT->position->y = yBase;
	gameObjects["gametext1"] = gtCredits;

	GameText * gtExit = new GameText();
	Transform *gtExitT = (Transform*)gtExit->getComponentById("transform");
	gtExitT->position->x = xBase;
	gtExitT->position->y = yBase-0.5;
	gameObjects["gametext2"] = gtExit;

	GameText * gtTitle = new GameText();
	Transform *gtTitleT = (Transform*)gtTitle->getComponentById("transform");
	gtTitleT->position->x = 0.3;
	gtTitleT->position->y = 0.7;
	gameObjects["title"] = gtTitle;
	

	Player * p = new Player();
	Transform * pt = (Transform*)p->getComponentById("transform");
	pt->position->x = -0.7;
	pt->position->y = 0.2;
	pt->position->z = 0.3;
	
	gameObjects["player"] = p;
	
	Tower * t = new Tower();
	Transform * tt = (Transform*)t->getComponentById("transform");
	tt->position->x= xBase+1.7;
	tt->position->y = yBase;
	gameObjects["tower"] = t;
	

}

void Menu::Init()
{
	glClearColor(0.3, 0.3, 0.3, 0.0);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glEnable(GL_TEXTURE_2D);

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

	glClearColor(.5f, .5f, .8f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glClearDepth(1.0f);
	//FIXME Transparency
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LEQUAL);
	
	Transform * gametextStart = (Transform*)((GameText*)gameObjects["gametext"])->getComponentById("transform");
	((GameText*)gameObjects["gametext"])->drawText("START");

	Transform * gametextTCredits = (Transform*)((GameText*)gameObjects["gametext1"])->getComponentById("transform");
	((GameText*)gameObjects["gametext1"])->drawText("CREDITS");

	Transform * gametextTExit = (Transform*)((GameText*)gameObjects["gametext2"])->getComponentById("transform");
	((GameText*)gameObjects["gametext2"])->drawText("EXIT");

	Transform * title = (Transform*)((GameText*)gameObjects["title"])->getComponentById("transform");
	((GameText*)gameObjects["title"])->drawText("TOWER DEFENSE");

	Transform * menuBarT1 = (Transform*)((MenuBar*)gameObjects["menubar1"])->getComponentById("transform");
	((MenuBar*)gameObjects["menubar1"])->draw();

	Transform * menuBarT2 = (Transform*)((MenuBar*)gameObjects["menubar2"])->getComponentById("transform");
	((MenuBar*)gameObjects["menubar2"])->draw();

	Transform * menuBarT3 = (Transform*)((MenuBar*)gameObjects["menubar3"])->getComponentById("transform");
	((MenuBar*)gameObjects["menubar3"])->draw();


	Transform * towerT = (Transform*)((Tower*)gameObjects["tower"])->getComponentById("transform");
	((Tower*)gameObjects["tower"])->draw();

	Transform * cameraT = (Transform*)((Camera*)gameObjects["camera"])->getComponentById("transform");
	Transform * playerT = (Transform*)((Player*)gameObjects["player"])->getComponentById("transform");

	gluLookAt(
		cameraT->position->x, cameraT->position->y, cameraT->position->z,
		playerT->position->x, playerT->position->y, playerT->position->z,
		1, 0, 1);


	((Player*)gameObjects["player"])->draw();

	glFlush();
	if (Application::instance()->getState()->isDoubleBufferActivated())
		glutSwapBuffers();
}

void Menu::Timer(int value)
{
	//rotate crystall
	Transform * towerT = (Transform*)((Camera*)gameObjects["tower"])->getComponentById("transform");
	towerT->rotation->z += 1;
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
	if (x > 0 && x < 150) {
		if (y > 0.5) {
			Application::instance()->getSceneManager()->changeScene("game");
		}
	}
}

void Menu::MouseMotion(int x, int y)
{

}

void Menu::MousePassiveMotion(int x, int y)
{
	if (x > 0 && x < 150) {
		//if (y > 0.5) {
			((MenuBar*)gameObjects["menubar1"])->changeColor();
//		}
	}
}