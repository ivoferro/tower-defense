#include <stdlib.h>
#include <string>
#include <GL/glut.h>
#include "../../headers/scenes/Game.h"
#include "../../headers/framework/Application.h"
#include "../../headers/util/Math.h"
#include "../../headers/gameobjects/Camera.h"
#include "../../headers/gameobjects/Enemy.h"
#include "../../headers/gameobjects/Boss.h"
#include "../../headers/gameobjects/Player.h"
#include "../../headers/gameobjects/GameText.h"
#include "../../headers/gameobjects/ShootingController.h"
#include "../../headers/gameobjects/Ground.h"
#include "../../headers/gameobjects/OuterWalls.h"
#include "../../headers/gameobjects/Wall.h"
#include "../../headers/gameobjects/Door.h"
#include "../../headers/gameobjects/Tower.h"
#include "../../headers/gameobjects/Plane.h"
#include "../../headers/gameobjects/Bullet.h"
#include "../../headers/gameobjects/SkyBox.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/Collider.h"
#include "../../headers/components/CharacterPhysics.h"
#include "../../headers/components/CameraSettings.h"
#include "../../headers/gameobjects/LifeBar.h"
#include "../../headers/gameobjects/MapObject.h"
#include "../../headers/util/Drawer.h"

//sound
#include <iostream>
#include<Windows.h>
#include<MMSystem.h>
using namespace std;


Game::Game() : level(this)
{
	Camera * c = new Camera();
	gameObjects["camera"] = c;

	Player * p = new Player();
	Transform * pt = (Transform*)p->getComponentById("transform");
	pt->position->x = 3;
	pt->position->z = 1.5;
	gameObjects["player"] = p;

	ShootingController * shootingController = new ShootingController(this);
	gameObjects["shootingController"] = shootingController;

	Wall * wall = new Wall();
	Transform * wallTransform = (Transform*)wall->getComponentById("transform");
	wallTransform->position->x = 25;
	wallTransform->position->y = 30;
	wallTransform->position->z = 3;
	wallTransform->scale->x = 20;
	wallTransform->scale->y = 20;
	wallTransform->scale->z = 6;
	gameObjects["wall1"] = wall;

	OuterWalls * outerWalls = new OuterWalls();
	gameObjects["outerWalls"] = outerWalls;

	SkyBox * skyBox = new SkyBox();
	gameObjects["skyBox"] = skyBox;

	Tower * t = new Tower();
	Transform * tt = (Transform*)t->getComponentById("transform");
	tt->position->z = 3;
	gameObjects["tower"] = t;

	Plane * plane = new Plane("stone");
	Transform * planeT = (Transform*)plane->getComponentById("transform");
	planeT->scale->x = 110;
	planeT->scale->y = 110;
	gameObjects["plane01"] = plane;
}

void Game::Init()
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

	initMapObjects();

	score = 0;

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
		gluPerspective(camSettings->fieldOfView, (GLfloat)width / height, 0.1, 100);
		break;
	}

	// Matrix Modelview
	// Matrix where the designed models transforms are made
	glMatrixMode(GL_MODELVIEW);
}

void Game::Draw()
{
	// FIXME NOT WORKING
	//debugDrawingActions();

	glClearColor(.9f, .9f, .9f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	Transform * cameraT = (Transform*)((Camera*)gameObjects["camera"])->getComponentById("transform");
	Transform * playerT = (Transform*)((Player*)gameObjects["player"])->getComponentById("transform");
	
	gluLookAt(
		cameraT->position->x, cameraT->position->y, cameraT->position->z,
		playerT->position->x, playerT->position->y, playerT->position->z, 
		0, 0, 1);

	for (std::map<std::string, GameObject*>::iterator it1 = gameObjects.begin(); it1 != gameObjects.end(); ++it1)
	{

		if (!dynamic_cast<MapObject*>(it1->second))
		{
			GameObject * obj = it1->second;
			obj->draw();
		}
	}

	// Display Map Objects
	glCallList(mapDisplayList);

	// Display Screen Text
	TextOverlayDraw();

	glFlush();
	if (Application::instance()->getState()->isDoubleBufferActivated())
		glutSwapBuffers();
}

void Game::Timer(int value)
{

	// has to be in this order, to prevent player from crossing objects
	// could be more clean!
	((Player*)gameObjects["player"])->isColliding = false;
	((Player*)gameObjects["player"])->timerActions(value);
	detectCollisions();
	((Player*)gameObjects["player"])->move();
	// order ends here

	moveCamera();

	// TODO refactor crystall
	//rotate crystall
	Transform * towerT = (Transform*)((Camera*)gameObjects["tower"])->getComponentById("transform");
	towerT->rotation->z += 1;

	if (Application::instance()->getState()->getInputs()->activate_wave)
	{
		level.startNextWave();
		Application::instance()->getState()->getInputs()->activate_wave = false;
	}
	if (Application::instance()->getState()->getInputs()->kill_all_enemies)
	{
		level.clearCurrentWave();
		Application::instance()->getState()->getInputs()->kill_all_enemies = false;
	}
	level.timerActions();

	// FIXME not the best place for this logic
	for (std::map<std::string, GameObject*>::iterator it1 = gameObjects.begin(); it1 != gameObjects.end(); ++it1)
	{
		GameObject * obj = it1->second;
		if (Enemy * e = dynamic_cast<Enemy*>(obj)) {
			e->timerActions();
			e->animate();
		}
		if (Boss * boss = dynamic_cast<Boss*>(obj)) {
			boss->timerActions();
			boss->animate();
		}
		else if (Bullet * b = dynamic_cast<Bullet*>(obj)) {
			b->timerActions();
		}
	}

	((ShootingController*)gameObjects["shootingController"])->timerActions();
	deleteBullets();

	glutPostRedisplay();
	((Player*)gameObjects["player"])->animate();
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
	case 'g':
	case 'G':
		Application::instance()->getState()->getInputs()->activate_wave = true;
		break;
	case 'k':
	case 'K':
		Application::instance()->getState()->getInputs()->kill_all_enemies = true;
		break;
	case 'p':
	case 'P':
		Application::instance()->getState()->getInputs()->kill_player = true;
		break;
	case 'n':
	case 'N':
		PlaySound(TEXT("resources/sound/sound.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
		break;

	case 'r':
	case 'R':
		Application::instance()->getSceneManager()->changeScene("game");
		break;
	case 'M':
	case 'm':
		PlaySound(NULL, NULL, 0);
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
	case 'g':
	case 'G':
		Application::instance()->getState()->getInputs()->activate_wave = false;
		break;
	case 'k':
	case 'K':
		Application::instance()->getState()->getInputs()->kill_all_enemies = false;
		break;

	case 'r':
	case 'R':
		Application::instance()->getSceneManager()->restartScene("game");
		break;
	case 'p':
	case 'P':
		Application::instance()->getState()->getInputs()->kill_player = false;
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
	if (mouse_state == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			Application::instance()->getState()->getInputs()->playerShooting = true;
			break;
		}
	}
	else
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			Application::instance()->getState()->getInputs()->playerShooting = false;
			break;
		}
	}
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
	CameraSettings * camSettings = (CameraSettings*)((Camera*)gameObjects["camera"])->getComponentById("settings");

	if (x > Application::instance()->getState()->mousePositionX)
	{
		// FIXME this logic should not be here, on the other hand there is not a
		// callback that triggers when mouse is not moving
		// Application::instance()->getState()->getInputs()->move_camera_left = true;
		playerT->rotation->z -= 2;
	}
	else if (x < Application::instance()->getState()->mousePositionX)
	{
		// FIXME this logic should not be here, on the other hand there is not a
		// callback that triggers when mouse is not moving
		// Application::instance()->getState()->getInputs()->move_camera_right = true;
		playerT->rotation->z += 2;
	}

	if (y > Application::instance()->getState()->mousePositionY)
	{
		if (camSettings->verticalInclination < camSettings->maxVerticalInclination)
		{
			camSettings->verticalInclination += 0.05;
		}
	}
	else if (y < Application::instance()->getState()->mousePositionY)
	{
		if (camSettings->verticalInclination > camSettings->minVerticalInclination)
		{
			camSettings->verticalInclination -= 0.05;
		}
	}

	// saves the last (x;y) positions to compare in the next call
	Application::instance()->getState()->mousePositionX = x;
	Application::instance()->getState()->mousePositionY = y;
}

void Game::detectCollisions()
{
	for (std::map<std::string, GameObject*>::iterator it1 = gameObjects.begin(); it1 != gameObjects.end(); ++it1)
	{
		GameObject * obj = it1->second;
		if (obj->hasComponent("collider"))
		{
			for (std::map<std::string, GameObject*>::iterator it2 = gameObjects.begin(); it2 != gameObjects.end(); ++it2)
			{
				GameObject * otherObj = it2->second;
				if (obj != otherObj)
				{
					((Collider*)obj->getComponentById("collider"))->testCollision(otherObj);
				}
			}
		}
	}
}

void Game::moveCamera()
{
	Transform * cameraT = (Transform*)((Camera*)gameObjects["camera"])->getComponentById("transform");
	Transform * playerT = (Transform*)((Player*)gameObjects["player"])->getComponentById("transform");
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

	// changes camera position according to player
	cameraT->position->x = playerT->position->x + (camSettings->distanceFromTarget * cos(Math::radians(playerT->rotation->z + 90)));
	cameraT->position->y = playerT->position->y + (camSettings->distanceFromTarget * sin(Math::radians(playerT->rotation->z + 90)));
	cameraT->position->z = camSettings->verticalInclination + playerT->position->z;
}

void Game::setLight()
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

void Game::setTextures()
{
	glEnable(GL_TEXTURE_2D);
	if (!Application::instance()->getTextures()->areTexturesLoaded) {
		Application::instance()->getTextures()->registerTexture("metal_plate", "resources/metal_plate.jpg");
		Application::instance()->getTextures()->registerTexture("stone", "resources/stone.jpg");

		Application::instance()->getTextures()->registerTexture("back", "resources/skybox/back.jpg");
		Application::instance()->getTextures()->registerTexture("front", "resources/skybox/front.jpg");
		Application::instance()->getTextures()->registerTexture("left", "resources/skybox/left.jpg");
		Application::instance()->getTextures()->registerTexture("right", "resources/skybox/right.jpg");
		Application::instance()->getTextures()->registerTexture("up", "resources/skybox/up.jpg");
	}
	Application::instance()->getTextures()->areTexturesLoaded = true;
}

void Game::deleteBullets()
{
	for (std::map<std::string, GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		GameObject * obj = it->second;
		if (Bullet * bullet = dynamic_cast<Bullet*>(obj)) {
			if (bullet->doRemove)
			{
				gameObjects.erase(it++);
				bullet->~Bullet();
			}
			else
			{
				++it;
			}
		}
	}
}

void Game::debugDrawingActions()
{
	if (!Application::instance()->getDebugger()->isActive)
	{
		return;
	}

	if (Application::instance()->getDebugger()->showColliders)
	{
		for (std::map<std::string, GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			GameObject * obj = it->second;
			if (obj->hasComponent("collider"))
			{
				Collider * collider = (Collider*)obj->getComponentById("collider");
				std::list<std::pair<Transform::Coordinates*, Transform::Coordinates*>> boxes = collider->getBoxes();
				for (const std::pair<Transform::Coordinates*, Transform::Coordinates*> box : boxes)
				{
					glPushMatrix();
					{
						glTranslatef(0.0f, 0.0f, 0.0f);
						if (obj->hasComponent("transform"))
						{
							Transform * t = (Transform*)obj->getComponentById("transform");
							glTranslatef(t->position->x, t->position->y, t->position->z);
							glRotatef(t->rotation->x, 1, 0, 0);
							glRotatef(t->rotation->y, 0, 1, 0);
							glRotatef(t->rotation->z, 0, 0, 1);
						}
						Drawer::drawBox(std::get<0>(box), std::get<1>(box));
					}
					glPopMatrix();
				}
			}
		}
	}
}

void Game::initMapObjects()
{
	mapDisplayList = glGenLists(1);

	// ******************************
	// Create Objects
	// barrel_brown
	MapObject * mapObj1 = new MapObject("resources/map/barrel_brown.mdl");
	Transform * t_mapObj1 = (Transform*)mapObj1->getComponentById("transform");
	t_mapObj1->scale->x = 0.05;
	t_mapObj1->scale->y = 0.05;
	t_mapObj1->scale->z = 0.05;
	t_mapObj1->position->x = 49;
	t_mapObj1->position->y = 15;
	t_mapObj1->position->z = 1;
	// camion
	MapObject * mapObj2 = new MapObject("resources/map/camion.mdl");
	Transform * t_mapObj2 = (Transform*)mapObj2->getComponentById("transform");
	t_mapObj2->scale->x = 0.05;
	t_mapObj2->scale->y = 0.05;
	t_mapObj2->scale->z = 0.05;
	t_mapObj2->position->x = 0;
	t_mapObj2->position->y = -38;
	t_mapObj2->rotation->z = 180;
	// kamen
	MapObject * mapObj3 = new MapObject("resources/map/kamen.mdl");
	Transform * t_mapObj3 = (Transform*)mapObj3->getComponentById("transform");
	t_mapObj3->scale->x = 0.5;
	t_mapObj3->scale->y = 0.5;
	t_mapObj3->scale->z = 0.5;
	t_mapObj3->position->x = 10;
	t_mapObj3->position->y = -38;
	// oil_barrel
	MapObject * mapObj4 = new MapObject("resources/map/oil_barrel_m1.mdl");
	Transform * t_mapObj4 = (Transform*)mapObj4->getComponentById("transform");
	t_mapObj4->scale->x = 0.06;
	t_mapObj4->scale->y = 0.06;
	t_mapObj4->scale->z = 0.06;
	t_mapObj4->position->x = 47;
	t_mapObj4->position->y = 47;
	// christmas_tree
	MapObject * mapObj5 = new MapObject("resources/map/christmastree.mdl");
	Transform * t_mapObj5 = (Transform*)mapObj5->getComponentById("transform");
	t_mapObj5->scale->x = 0.05;
	t_mapObj5->scale->y = 0.05;
	t_mapObj5->scale->z = 0.05;
	t_mapObj5->position->x = 10;
	t_mapObj5->position->y = -24;
	// skeleton
	MapObject * mapObj6 = new MapObject("resources/map/skeleton.mdl");
	Transform * t_mapObj6 = (Transform*)mapObj6->getComponentById("transform");
	t_mapObj6->scale->x = 0.05;
	t_mapObj6->scale->y = 0.05;
	t_mapObj6->scale->z = 0.05;
	t_mapObj6->position->x = -40;
	t_mapObj6->position->y = 35;
	// train (1)
	MapObject * mapObj7 = new MapObject("resources/map/guterwagen.mdl");
	Transform * t_mapObj7 = (Transform*)mapObj7->getComponentById("transform");
	t_mapObj7->scale->x = 0.07;
	t_mapObj7->scale->y = 0.07;
	t_mapObj7->scale->z = 0.07;
	t_mapObj7->position->x = -38;
	t_mapObj7->position->y = 15;;
	// train (2)
	MapObject * mapObj8 = new MapObject("resources/map/hbtest.mdl");
	Transform * t_mapObj8 = (Transform*)mapObj8->getComponentById("transform");
	t_mapObj8->scale->x = 0.07;
	t_mapObj8->scale->y = 0.07;
	t_mapObj8->scale->z = 0.07;
	t_mapObj8->position->x = -16;
	t_mapObj8->position->y = 15;
	// sandbags (1)
	MapObject * mapObj9 = new MapObject("resources/map/sandbags.mdl");
	Transform * t_mapObj9 = (Transform*)mapObj9->getComponentById("transform");
	t_mapObj9->scale->x = 0.05;
	t_mapObj9->scale->y = 0.05;
	t_mapObj9->scale->z = 0.05;
	t_mapObj9->position->x = 6;
	t_mapObj9->position->y = -24;
	// pc_MobileOffice (1)
	MapObject * mapObj10 = new MapObject("resources/map/pc_MobileOffice.mdl");
	Transform * t_mapObj10 = (Transform*)mapObj10->getComponentById("transform");
	t_mapObj10->scale->x = 0.05;
	t_mapObj10->scale->y = 0.05;
	t_mapObj10->scale->z = 0.05;
	t_mapObj10->position->x = -18;
	t_mapObj10->position->y = -40;
	t_mapObj10->rotation->z = 90;
	// AA_RangeTower_Height2_KN_Smesh
	MapObject * mapObj11 = new MapObject("resources/map/AA_RangeTower_Height2_KN_Smesh.mdl");
	Transform * t_mapObj11 = (Transform*)mapObj11->getComponentById("transform");
	t_mapObj11->scale->x = 0.05;
	t_mapObj11->scale->y = 0.05;
	t_mapObj11->scale->z = 0.05;
	t_mapObj11->position->x = 8;
	t_mapObj11->position->y = -45;
	// sandbags (2)
	MapObject * mapObj12 = new MapObject("resources/map/sandbags.mdl");
	Transform * t_mapObj12 = (Transform*)mapObj12->getComponentById("transform");
	t_mapObj12->scale->x = 0.05;
	t_mapObj12->scale->y = 0.05;
	t_mapObj12->scale->z = 0.05;
	t_mapObj12->position->x = 8;
	t_mapObj12->position->y = -24;
	// halftrack_us1
	MapObject * mapObj13 = new MapObject("resources/map/halftrack_us1.mdl");
	Transform * t_mapObj13 = (Transform*)mapObj13->getComponentById("transform");
	t_mapObj13->scale->x = 0.05;
	t_mapObj13->scale->y = 0.05;
	t_mapObj13->scale->z = 0.05;
	t_mapObj13->position->x = -8;
	t_mapObj13->position->y = 25.5;
	t_mapObj13->position->z = 2.3;
	t_mapObj13->rotation->z = 180;
	// AF_tent_military
	MapObject * mapObj14 = new MapObject("resources/map/AF_tent_military.mdl");
	Transform * t_mapObj14 = (Transform*)mapObj14->getComponentById("transform");
	t_mapObj14->scale->x = 0.05;
	t_mapObj14->scale->y = 0.05;
	t_mapObj14->scale->z = 0.05;
	t_mapObj14->position->x = -41;
	t_mapObj14->position->y = 35;
	// AF_outdoors_kiosk
	MapObject * mapObj15 = new MapObject("resources/map/AF_outdoors_kiosk.mdl");
	Transform * t_mapObj15 = (Transform*)mapObj15->getComponentById("transform");
	t_mapObj15->scale->x = 0.05;
	t_mapObj15->scale->y = 0.05;
	t_mapObj15->scale->z = 0.05;
	t_mapObj15->position->x = 8;
	t_mapObj15->position->y = -30;
	// AA_Tent
	MapObject * mapObj16 = new MapObject("resources/map/AA_Tent.mdl");
	Transform * t_mapObj16 = (Transform*)mapObj16->getComponentById("transform");
	t_mapObj16->scale->x = 0.05;
	t_mapObj16->scale->y = 0.05;
	t_mapObj16->scale->z = 0.05;
	t_mapObj16->position->x = -42;
	t_mapObj16->position->y = -30;
	// pc_MobileOffice (2)
	MapObject * mapObj17 = new MapObject("resources/map/pc_MobileOffice.mdl");
	Transform * t_mapObj17 = (Transform*)mapObj17->getComponentById("transform");
	t_mapObj17->scale->x = 0.05;
	t_mapObj17->scale->y = 0.05;
	t_mapObj17->scale->z = 0.05;
	t_mapObj17->position->x = -18;
	t_mapObj17->position->y = -25;
	t_mapObj17->rotation->z = 90;
	// pc_MobileOffice (3)
	MapObject * mapObj18 = new MapObject("resources/map/pc_MobileOffice.mdl");
	Transform * t_mapObj18 = (Transform*)mapObj18->getComponentById("transform");
	t_mapObj18->scale->x = 0.05;
	t_mapObj18->scale->y = 0.05;
	t_mapObj18->scale->z = 0.05;
	t_mapObj18->position->x = -18;
	t_mapObj18->position->y = -10;
	t_mapObj18->rotation->z = 90;
	// pc_MobileOffice (4)
	MapObject * mapObj19 = new MapObject("resources/map/pc_MobileOffice.mdl");
	Transform * t_mapObj19 = (Transform*)mapObj19->getComponentById("transform");
	t_mapObj19->scale->x = 0.05;
	t_mapObj19->scale->y = 0.05;
	t_mapObj19->scale->z = 0.05;
	t_mapObj19->position->x = -33;
	t_mapObj19->position->y = -7;
	t_mapObj19->rotation->z = 180;
	// house_zd_001
	MapObject * mapObj20 = new MapObject("resources/map/house_zd_001.mdl");
	Transform * t_mapObj20 = (Transform*)mapObj20->getComponentById("transform");
	t_mapObj20->scale->x = 0.055;
	t_mapObj20->scale->y = 0.05;
	t_mapObj20->scale->z = 0.05;
	t_mapObj20->position->x = 35;
	t_mapObj20->position->y = -39;
	t_mapObj20->position->z = 0.7;
	// maniak_garage (1)
	MapObject * mapObj21 = new MapObject("resources/map/maniak_garage.mdl");
	Transform * t_mapObj21 = (Transform*)mapObj21->getComponentById("transform");
	t_mapObj21->scale->x = 0.06;
	t_mapObj21->scale->y = 0.06;
	t_mapObj21->scale->z = 0.06;
	t_mapObj21->position->x = 39;
	t_mapObj21->position->y = -24;
	t_mapObj21->position->z = 0;
	// maniak_garage (2)
	MapObject * mapObj22 = new MapObject("resources/map/maniak_garage.mdl");
	Transform * t_mapObj22 = (Transform*)mapObj22->getComponentById("transform");
	t_mapObj22->scale->x = 0.06;
	t_mapObj22->scale->y = 0.06;
	t_mapObj22->scale->z = 0.06;
	t_mapObj22->position->x = 31;
	t_mapObj22->position->y = -24;
	t_mapObj22->position->z = 0;
	// copcar2
	MapObject * mapObj23 = new MapObject("resources/map/copcar2.mdl");
	Transform * t_mapObj23 = (Transform*)mapObj23->getComponentById("transform");
	t_mapObj23->scale->x = 0.05;
	t_mapObj23->scale->y = 0.05;
	t_mapObj23->scale->z = 0.05;
	t_mapObj23->position->x = 10;
	t_mapObj23->position->y = -15;
	t_mapObj23->position->z = 1;
	t_mapObj23->rotation->z = 90;
	// jagd
	MapObject * mapObj24 = new MapObject("resources/map/jagd.mdl");
	Transform * t_mapObj24 = (Transform*)mapObj24->getComponentById("transform");
	t_mapObj24->scale->x = 0.05;
	t_mapObj24->scale->y = 0.05;
	t_mapObj24->scale->z = 0.05;
	t_mapObj24->position->x = 44;
	t_mapObj24->position->y = 5;
	t_mapObj24->rotation->z = 90;
	// oldpickup
	MapObject * mapObj25 = new MapObject("resources/map/oldpickup.mdl");
	Transform * t_mapObj25 = (Transform*)mapObj25->getComponentById("transform");
	t_mapObj25->scale->x = 0.05;
	t_mapObj25->scale->y = 0.05;
	t_mapObj25->scale->z = 0.05;
	t_mapObj25->position->x = -5;
	t_mapObj25->position->y = 45;

	/*gameObjects["mapObject1"] = mapObj1;
	gameObjects["mapObject2"] = mapObj2;
	gameObjects["mapObject3"] = mapObj3;
	gameObjects["mapObject4"] = mapObj4;
	gameObjects["mapObject5"] = mapObj5;
	gameObjects["mapObject6"] = mapObj6;
	gameObjects["mapObject7"] = mapObj7;
	gameObjects["mapObject8"] = mapObj8;
	gameObjects["mapObject9"] = mapObj9;
	gameObjects["mapObject10"] = mapObj10;
	gameObjects["mapObject11"] = mapObj11;
	gameObjects["mapObject12"] = mapObj12;
	gameObjects["mapObject13"] = mapObj13;
	gameObjects["mapObject14"] = mapObj14;
	gameObjects["mapObject15"] = mapObj15;
	gameObjects["mapObject16"] = mapObj16;
	gameObjects["mapObject17"] = mapObj17;
	gameObjects["mapObject18"] = mapObj18;
	gameObjects["mapObject19"] = mapObj19;
	gameObjects["mapObject20"] = mapObj20;
	gameObjects["mapObject21"] = mapObj21;
	gameObjects["mapObject22"] = mapObj22;
	gameObjects["mapObject23"] = mapObj23;
	gameObjects["mapObject24"] = mapObj24;
	gameObjects["mapObject25"] = mapObj25;*/

	// ******************************
	// Create DisplayList
	glNewList(mapDisplayList, GL_COMPILE);

	mapObj1->draw();
	mapObj2->draw();
	mapObj3->draw();
	mapObj4->draw();
	mapObj5->draw();
	mapObj6->draw();
	mapObj7->draw();
	mapObj8->draw();
	mapObj9->draw();
	mapObj10->draw();
	mapObj11->draw();
	mapObj12->draw();
	mapObj13->draw();
	mapObj14->draw();
	mapObj15->draw();
	mapObj16->draw();
	mapObj17->draw();
	mapObj18->draw();
	mapObj19->draw();
	mapObj20->draw();
	mapObj21->draw();
	mapObj22->draw();
	mapObj23->draw();
	mapObj24->draw();
	mapObj25->draw();

	glEndList();
}

void displayBitMapText(char * text, void *font, int x, int y)
{
	glPushMatrix();
	int length = strlen(text);
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(font, (int)text[i]);
	}
	glPopMatrix();
}

void displayStrokeText(char * text, void *font, int x, int y)
{
	glPushMatrix();
	int length = strlen(text);
	//glRasterPos2i(x, y);
	glTranslatef(50, 300, 0);
	for (int i = 0; i < length; i++) {
		glutStrokeCharacter(font, (int)text[i]);
	}
	glPopMatrix();
}

void Game::TextLogic()
{
	char* scoreLabel = "SCORE: ";
	char* gameover = "GAMEOVER";
	char* victory = "VICTORY";
	char* gameMode = "GAME MODE: ";
	char* combateMode = "COMBATE MODE [PRESS K TO KILL ALL ENEMIES]";
	char* pauseMode = "PAUSE MODE [PRESS G TO START NEXT WAVE]";
	// SCORE
	char scoreValue[12];
	sprintf(scoreValue, "%d", score);
	displayBitMapText(scoreLabel, GLUT_BITMAP_9_BY_15, 10, 10);
	displayBitMapText(scoreValue, GLUT_BITMAP_9_BY_15, 100, 10);

	// GAME MODE
	if (!((Player*)gameObjects["player"])->isAlive || ((Tower*)gameObjects["tower"])->gameover)
	{
		displayStrokeText(gameover, GLUT_STROKE_ROMAN, 10, 0);
	}
	else
	{
		displayBitMapText(gameMode, GLUT_BITMAP_9_BY_15, 10, 580);
		if (level.phase == Level::Phase::COMBAT)
		{
			displayBitMapText(combateMode, GLUT_BITMAP_9_BY_15, 80, 580);
		}
		else if (level.phase == Level::Phase::WAVE_CLEAR ||
			level.phase == Level::Phase::INITIAL)
		{
			displayBitMapText(pauseMode, GLUT_BITMAP_9_BY_15, 80, 580);
		}
		else if (level.phase == Level::Phase::VICTORY)
		{
			displayStrokeText(victory, GLUT_STROKE_MONO_ROMAN, 10, 0);
		}
	}
}

void Game::TextOverlayDraw()
{

	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();

	// PUT TEXT LOGIC HERE **********************

	TextLogic();

	// ******************************************

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}