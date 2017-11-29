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
	createGameObjects();
	
}

void Menu::Init()
{
	setLight();
	setTextures();

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

	glClearColor(.1f, .1f, .2f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	drawGameObjects();

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
	if (button == GLUT_LEFT_BUTTON && mouse_state == GLUT_DOWN) {
	
		MenuBar* start=(MenuBar*)gameObjects["menubar1"];
		double width = start->getWidth();
		double height = start->getHeight();
	
		Transform *gtExitT = (Transform*)start->getComponentById("transform");
		double xBar=abs(gtExitT->position->x);
		double test = height;
		double yBar = abs(gtExitT->position->y);

		//FIXME - position relative (window callback)

		if (x < (width+xBar)*125 && y>(yBar-height)*243 && y<(yBar)*310){
				Application::instance()->getSceneManager()->changeScene("game");
			}
		}

	
}

void Menu::MouseMotion(int x, int y)
{

}

void Menu::CloseFunc()
{
	//TODO

}


//TODO
void Menu::WindowSize() {

}
//TODO
void Menu::MousePassiveMotion(int x, int y)
{
}

bool Menu:: isInsideStart(int x, int y, int xMax, int yMax) {
	
	if (x < 0.5 + xMax)
		return true;

	//FIXME consider Y
	//if (y <-0.5)
	//	return true;
	return false;
}

void Menu::createGameObjects() {
	int xBase = -1;
	int xBaseText = xBase;
	int yBase = 0;

	Camera * c = new Camera();
	gameObjects["camera"] = c;

	// -------------------------- START BAR ----------------------------//
	MenuBar *mb = new MenuBar();
	Transform *mbT1 = (Transform*)mb->getComponentById("transform");
	mbT1->position->x = xBase;
	mbT1->position->y = yBase-0.5;
	mbT1->position->z = yBase - 0.5;
	gameObjects["menubar1"] = mb;
	// -------------------------- CREDITS BAR --------------------------//
	MenuBar *mb2 = new MenuBar();
	Transform *mbT2 = (Transform*)mb2->getComponentById("transform");
	mbT2->position->x = xBase;
	mbT2->position->y = yBase;
	gameObjects["menubar2"] = mb2;

	// -------------------------- EXIT BAR ------------------------------//
	MenuBar *mb3 = new MenuBar();
	Transform *mbT3 = (Transform*)mb3->getComponentById("transform");
	mbT3->position->x = xBase;
	mbT3->position->y = yBase + 0.5;
	gameObjects["menubar3"] = mb3;

	//----------------------- OPTIONS -----------------------------------//

	GameText * gtStart = new GameText("Start");
	Transform *gtStartT = (Transform*)gtStart->getComponentById("transform");
	gtStartT->position->x = xBaseText;
	gtStartT->position->y = yBase + 0.5;
	gameObjects["gametext"] = gtStart;

	GameText * gtCredits = new GameText("Credits");
	Transform *gtCreditsT = (Transform*)gtCredits->getComponentById("transform");
	gtCreditsT->position->x = xBaseText;
	gtCreditsT->position->y = yBase;
	gameObjects["gametext1"] = gtCredits;

	GameText * gtExit = new GameText("Exit");
	Transform *gtExitT = (Transform*)gtExit->getComponentById("transform");
	gtExitT->position->x = xBaseText;
	gtExitT->position->y = yBase - 0.5;
	gameObjects["gametext2"] = gtExit;

	//================================================================
	GameText * gtTitle = new GameText("Tower Defense");
	Transform *gtTitleT = (Transform*)gtTitle->getComponentById("transform");
	gtTitleT->position->x = 0.3;
	gtTitleT->position->y = 0.7;
	gameObjects["title"] = gtTitle;

	//-----------------------------------------------------------------------

	Player * p = new Player();
	Transform * pt = (Transform*)p->getComponentById("transform");
	pt->position->x = -0.7;
	pt->position->y = 0.2;
	pt->position->z = 0.3;

	gameObjects["player"] = p;

	Tower * t = new Tower();
	Transform * tt = (Transform*)t->getComponentById("transform");
	tt->rotation->x = -90.0;
	tt->position->x = xBase + 1.7;
	tt->position->y = yBase - 0.75;
	tt->scale->x = 0.25;
	tt->scale->y = 0.25;
	tt->scale->z = 0.25;
	gameObjects["tower"] = t;
	
}

void Menu::setLight()
{
	GLfloat light_ambient[] = { 0.9f, 0.85f, 0.85f, 1.0f };
	GLfloat light_diffuse[] = { 0.95f, 0.95f, 0.95f, 1.0f };
	GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat light_position[] = { 0.0f, 5.0f, 0.0f, 0.0f };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
}

void Menu::setTextures()
{
	glEnable(GL_TEXTURE_2D);
	Application::instance()->getTextures()->registerTexture("vinil", "resources/vinil.jpg");
	Application::instance()->getTextures()->registerTexture("vinil2", "resources/vinil2.jpg");
}

void Menu::drawGameObjects() {

	//----------------------- BARS ------------------------//
	Transform * menuBarT1 = (Transform*)((MenuBar*)gameObjects["menubar1"])->getComponentById("transform");
	((MenuBar*)gameObjects["menubar1"])->draw();

	Transform * menuBarT2 = (Transform*)((MenuBar*)gameObjects["menubar2"])->getComponentById("transform");
	((MenuBar*)gameObjects["menubar2"])->draw();

	Transform * menuBarT3 = (Transform*)((MenuBar*)gameObjects["menubar3"])->getComponentById("transform");
	((MenuBar*)gameObjects["menubar3"])->draw();

	//----------------------- TEXT OPTIONS ------------------------//
	Transform * gametextStart = (Transform*)((GameText*)gameObjects["gametext"])->getComponentById("transform");
	((GameText*)gameObjects["gametext"])->drawText();
	
	Transform * gametextTCredits = (Transform*)((GameText*)gameObjects["gametext1"])->getComponentById("transform");
	((GameText*)gameObjects["gametext1"])->drawText();
	
	Transform * gametextTExit = (Transform*)((GameText*)gameObjects["gametext2"])->getComponentById("transform");
	((GameText*)gameObjects["gametext2"])->drawText();

	//-----------------------TITLE OPTION ------------------------//
	Transform * title = (Transform*)((GameText*)gameObjects["title"])->getComponentById("transform");
	((GameText*)gameObjects["title"])->drawText();
	//------------------------------------------------------------//

	Transform * towerT = (Transform*)((Tower*)gameObjects["tower"])->getComponentById("transform");
	((Tower*)gameObjects["tower"])->draw();

	Transform * cameraT = (Transform*)((Camera*)gameObjects["camera"])->getComponentById("transform");
	Transform * playerT = (Transform*)((Player*)gameObjects["player"])->getComponentById("transform");

	gluLookAt(
	cameraT->position->x, cameraT->position->y, cameraT->position->z,
	playerT->position->x, playerT->position->y, playerT->position->z,
	1, 0, 1);

	((Player*)gameObjects["player"])->draw();
}