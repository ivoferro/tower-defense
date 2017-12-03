#include <stdlib.h>
#include "../../headers/scenes/Menu.h"
#include "../../headers/framework/Application.h"
#include "../../headers/components/Transform.h"
#include "../../headers/gameobjects/GameText.h"
#include "../../headers/gameobjects/TextBox.h"
#include "../../headers/gameobjects/Player.h"
#include "../../headers/gameobjects/Tower.h"
#include "../../headers/gameobjects/MenuBar.h"

//sound
#include <iostream>
#include<Windows.h>
#include<MMSystem.h>
using namespace std;


Menu::Menu()
{
	createGameObjects();
}

void Menu::Init()
{
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	setLight();
	setTextures();

	glutPostRedisplay();
}

void Menu::Reshape(int width, int height)
{
	this->width = width;
	this->height = height;
	GLint size;
	GLfloat ratio = (GLfloat)width / height;
	GLfloat ratio1 = (GLfloat)height / width;

	if (width < height)
		size = width;
	else
		size = height;


	// glViewport(botom, left, width, height)
	// define the part of the window to be used by OpenGL

	glViewport(0, 0, (GLint)width, (GLint)height);

	// gluOrtho2D(left,right,bottom,top); 
	// 2D orthogonal projection, with a depth of (Z) between -1 and 1
	if (width < height)
		gluOrtho2D(-1, 1, -1 * ratio1, 1 * ratio1);
	else
		gluOrtho2D(-1 * ratio, 1 * ratio, -1, 1);

	//Matrix Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Matrix Modelview
	// Matrix where the designed models transforms are made
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
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
	Transform * towerT = (Transform*)(gameObjects["tower"])->getComponentById("transform");
	towerT->rotation->z += 1;
}

void Menu::Key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'S':
	case 's':
		startGame();
		break;
	case 'E':
	case 'e':
		exit(0);
		break;
	case 'N':
	case 'n':
		PlaySound(TEXT("resources/sound/sound.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
		break;
	case 'M':
	case 'm':
		PlaySound(NULL, NULL, 0);
		break;
	}
	if (key == 'h' || key == 'H') {
		help();
	}
	if (key == 'c' || key == 'C') {
		credits();
	}

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

		setSelection(x, y);

		if (id == 1) {
			startGame();
		}
		if (id == 2) {
			help();
		}
		if (id == 3) {
			credits();		
		}
		if (id == 4)	
			exit(0);
	}
	glPopMatrix();
	glPopMatrix();

}

void Menu::MouseMotion(int x, int y)
{
}

void Menu::MousePassiveMotion(int x, int y)
{
	setSelection(x,y);

	if (id == 0) {
		clearText();
		dragOptions(-0.5);
		Transform *t = (Transform*)(gameObjects["title"])->getComponentById("transform");
		t->position->x = 0.1;
		PlaySound(NULL, NULL, 0);
	}

	if (id == 1) {	
		Transform * titleT1 = (Transform*)(gameObjects["menubar1"])->getComponentById("transform");
		titleT1->position->x = -0.6;	
	}
	if (id == 2) {
		Transform * titleT4 = (Transform*)(gameObjects["helpbar"])->getComponentById("transform");
		titleT4->position->x = -0.6;
	}
	if (id == 3) {
		Transform * titleT2 = (Transform*)(gameObjects["menubar2"])->getComponentById("transform");
		titleT2->position->x = -0.6;
	}
	if (id == 4) {
		Transform * titleT3 = (Transform*)(gameObjects["menubar3"])->getComponentById("transform");
		titleT3->position->x = -0.6;
	}

	glPopMatrix();
	glPopMatrix();
}

void Menu::createGameObjects() {
	double coordBars[4][3] = { {-0.3,0.7,0}, {-0.3,0.2,0}, {-0.3,-0.3,0},{-0.3,-0.8,0} };

	// -------------------------- START BAR ----------------------------//
	MenuBar *mb = new MenuBar();
	Transform *mbT1 = (Transform*)mb->getComponentById("transform");

	mbT1->position->x = coordBars[0][0];
	mbT1->position->y = coordBars[0][1];
	mbT1->position->z = coordBars[0][2];
	gameObjects["menubar1"] = mb;

	// -------------------------- HELP BAR ----------------------------//
	MenuBar *hb = new MenuBar();
	Transform *hbT = (Transform*)hb->getComponentById("transform");
	hbT->position->x = coordBars[1][0];
	hbT->position->y = coordBars[1][1];
	hbT->position->z = coordBars[1][2];
	gameObjects["helpbar"] = hb;

	TextBox *help = new TextBox();
	Transform *ht = (Transform*)help->getComponentById("transform");
	ht->position->x = 2;
	ht->position->y = 0.7;
	gameObjects["helpBox"] = help;

	// -------------------------- CREDITS BAR --------------------------//
	MenuBar *mb2 = new MenuBar();
	Transform *mbT2 = (Transform*)mb2->getComponentById("transform");
	mbT2->position->x = coordBars[2][0];
	mbT2->position->y = coordBars[2][1];
	mbT2->position->z = coordBars[2][2];
	gameObjects["menubar2"] = mb2;


	TextBox *credits = new TextBox();
	Transform *ct = (Transform*)credits->getComponentById("transform");
	ct->position->x = 2;
	ct->position->y = 0.7;
	gameObjects["creditsBox"] = credits;

	// -------------------------- EXIT BAR ------------------------------//
	MenuBar *mb3 = new MenuBar();
	Transform *mbT3 = (Transform*)mb3->getComponentById("transform");
	mbT3->position->x = coordBars[3][0];
	mbT3->position->y = coordBars[3][1];
	mbT3->position->z = coordBars[3][2];
	gameObjects["menubar3"] = mb3;
	//-------------------------- TITLE ----------------------------------//
	GameText *title = new GameText("TOWER DEFENSE");
	Transform *titleT = (Transform*)title->getComponentById("transform");
	titleT->position->x = 0.1;
	titleT->position->y = 0.7;
	gameObjects["title"] = title;

	//-----------------------------------------------------------------------
	Player * p = new Player();
	Transform * pt = (Transform*)p->getComponentById("transform");
	pt->position->x = 0.4;
	pt->position->y = -0.2;
	pt->position->z = 0.3;
	pt->scale->x = 0.35;
	pt->scale->y = 0.35;
	pt->scale->z = 0.35;
	pt->rotation->z = 0;
	pt->rotation->y = 180;
	pt->rotation->x = 90;

	gameObjects["player"] = p;

	Tower * t = new Tower();
	Transform * tt = (Transform*)t->getComponentById("transform");
	tt->position->x = 0;
	tt->position->y = -0.2;
	tt->position->z = -0.5;
	tt->scale->x = 0.20;
	tt->scale->y = 0.20;
	tt->scale->z = 0.20;
	tt->rotation->x = -90;

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

	//----------------- SELECTION MODE ----------------//
	int i;
	GLint viewport[4];
	GLdouble modelview[16], projMatrix[16];
	GLdouble x, y, z;

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	for (i = 0; i < 4; i++)
		gluProject(coordBars[i][0], coordBars[i][1], coordBars[i][2], modelview, projMatrix, viewport, &x, &y, &z);

	//----------------------- MENU OPTIONS ------------------------//
	GLfloat whitecolor[3] = { 1.0, 1.0, 1.0 };
	GLfloat blackcolor[3] = { 0.0, 0.0, 0.0 };
	
	glPushName(4);
	((MenuBar*)gameObjects["menubar1"])->drawWithText("Start", whitecolor);
	glPopName();

	glPushName(3);
	((MenuBar*)gameObjects["helpbar"])->drawWithText("Help", whitecolor);
	glPopName();

	glPushName(2);
	((MenuBar*)gameObjects["menubar2"])->drawWithText("Credits", whitecolor);
	glPopName();

	glPushName(1);
	((MenuBar*)gameObjects["menubar3"])->drawWithText("Exit", whitecolor);
	glPopName();

	//-----------------------CREDITS BOX ------------------------//
	((TextBox*)gameObjects["creditsBox"])->draw();
	char* creditsText[] = { "TOWER DEFENSE", "Daniel Goncalves", "Diana Godinho", "Ivo Ferro", "Pedro Fernandes" };
	((TextBox*)gameObjects["creditsBox"])->drawWithText(creditsText, 5);

	//----------------------HELP BOX-----------------------------//
	((TextBox*)gameObjects["helpBox"])->draw();
	char* helpText[] = { "HELP", "Move front: w", "Move left: a", "Move right: d",
						"Shoot: left click", "Restart game: r", 
						"Mute sound: m", "Unmute sound: n","Zoom In: 1", "Zoom Out: 2" };
	((TextBox*)gameObjects["helpBox"])->drawWithText(helpText, 10);
	//-----------------------------------------------------------//
	((GameText*)gameObjects["title"])->draw();

	//((Tower*)gameObjects["tower"])->draw();
	((Player*)gameObjects["player"])->draw();
	
}

void Menu::setSelection(int x, int y) {
	GLuint selectBuffer[100], *ptr;
	int i, hits;
	double zmin = 10.0;
	GLint viewport[4];
	GLdouble modelview[16], projMatrix[16];

	//to store the selections (Picking)
	glSelectBuffer(100, selectBuffer);

	//to start the fake drawing process (Picking)
	glRenderMode(GL_SELECT);
	glInitNames();

	// The projection matrix
	// Matriz onde se define como o mundo e apresentado na janela
	// Matrix where you define how the world is shown in the window
	glPushMatrix();

	//if we were picking
	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	glLoadIdentity();

	//to specify the selection region
	glGetIntegerv(GL_VIEWPORT, viewport);
	gluPickMatrix((GLdouble)x, (GLdouble)y, 1, 1, viewport);
	//gluPerspective(0.0, (double)width / (double)height, 0.1, 10.0);

	//create Modelview matrix
	glMatrixMode(GL_MODELVIEW);
	drawGameObjects();
	//create Projection matrix
	hits = glRenderMode(GL_RENDER);

	if (hits > 0)
	{
		ptr = selectBuffer;
		for (i = 0; i < hits; i++)
		{
			if (zmin >(double) ptr[1] / 0xffffffff)
			{
				zmin = (double)ptr[1] / 0xffffffff;
				id = ptr[3];
			}
			ptr += 4;
		}
		glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		gluUnProject(x, y, zmin, modelview, projMatrix, viewport, &coordBars[0][0], &coordBars[0][1], &coordBars[0][2]);
	}
	else
		id = 0;
}

void Menu::dragOptions(GLfloat pos) {

	Transform * menuBar1 = (Transform*)(gameObjects["menubar1"])->getComponentById("transform");
	menuBar1->position->x = pos;

	Transform * menuBar2 = (Transform*)(gameObjects["menubar2"])->getComponentById("transform");
	menuBar2->position->x = pos;

	Transform * helpBar = (Transform*)(gameObjects["helpbar"])->getComponentById("transform");
	helpBar->position->x = pos;

	Transform * menuBar3 = (Transform*)(gameObjects["menubar3"])->getComponentById("transform");
	menuBar3->position->x = pos;
}

void Menu::clearText() {
	GLfloat clear=2.0;
	Transform *creditsT = (Transform*)(gameObjects["creditsBox"])->getComponentById("transform");
	creditsT->position->x = clear;
	Transform * helpT = (Transform*)(gameObjects["helpBox"])->getComponentById("transform");
	helpT->position->x = clear;
}

void Menu::startGame() {
	PlaySound(TEXT("resources/sound/sound.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	Application::instance()->getSceneManager()->changeScene("game");
}

void Menu::help() {
	clearText();
	Transform *ht = (Transform*)(gameObjects["helpBox"])->getComponentById("transform");
	ht->position->x = 0.5;
	Transform *t = (Transform*)(gameObjects["title"])->getComponentById("transform");
	t->position->x = 2;

	PlaySound(TEXT("resources/sound/explosion.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	glutWarpPointer(width / 2, height / 2);
}

void Menu::credits() {
	clearText();
	Transform *creditsT = (Transform*)(gameObjects["creditsBox"])->getComponentById("transform");
	creditsT->position->x = 0.4;

	Transform *t = (Transform*)(gameObjects["title"])->getComponentById("transform");
	t->position->x = 2;

	PlaySound(TEXT("resources/sound/credits.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	glutWarpPointer(width / 2, height / 2);
}