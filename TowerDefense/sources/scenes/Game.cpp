#include <stdlib.h>
#include <GL/glut.h>
#include "../../headers/scenes/Game.h"
#include "../../headers/framework/Application.h"
#include "../../headers/util/Math.h"
#include "../../headers/gameobjects/Camera.h"
#include "../../headers/gameobjects/Enemy.h"
#include "../../headers/gameobjects/Player.h"
#include "../../headers/gameobjects/ShootingController.h"
#include "../../headers/gameobjects/Ground.h"
#include "../../headers/gameobjects/OuterWalls.h"
#include "../../headers/gameobjects/Wall.h"
#include "../../headers/gameobjects/Door.h"
#include "../../headers/gameobjects/Tower.h"
#include "../../headers/gameobjects/Plane.h"
#include "../../headers/gameobjects/Bullet.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/Collider.h"
#include "../../headers/components/CharacterPhysics.h"
#include "../../headers/components/CameraSettings.h"
#include "../../headers/gameobjects/LifeBar.h"
#include "../../headers/gameobjects/MapObject.h"

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
	Collider * wallCollider = (Collider*)wall->getComponentById("collider");
	wallCollider->addBox(
		new Transform::Coordinates(10, 10, 3),
		new Transform::Coordinates(-10, -10, -3));
	gameObjects["wall1"] = wall;

	Tower * t = new Tower();
	Transform * tt = (Transform*)t->getComponentById("transform");
	gameObjects["tower"] = t;

	Plane * plane = new Plane("rock_floor");
	Transform * planeT = (Transform*)plane->getComponentById("transform");
	planeT->scale->x = 100;
	planeT->scale->y = 100;
	gameObjects["plane01"] = plane;
	
	// barrel_brown
	MapObject * mapObj1 = new MapObject("resources/map/barrel_brown.mdl");
	Transform * t_mapObj1 = (Transform*)mapObj1->getComponentById("transform");
	t_mapObj1->scale->x = 0.05;
	t_mapObj1->scale->y = 0.05;
	t_mapObj1->scale->z = 0.05;
	t_mapObj1->position->x = 45;
	t_mapObj1->position->y = 45;
	t_mapObj1->position->z = 1;
	gameObjects["mapObject01"] = mapObj1;

	// camion
	MapObject * mapObj2 = new MapObject("resources/map/camion.mdl");
	Transform * t_mapObj2 = (Transform*)mapObj2->getComponentById("transform");
	t_mapObj2->scale->x = 0.05;
	t_mapObj2->scale->y = 0.05;
	t_mapObj2->scale->z = 0.05;
	t_mapObj2->position->x = 0;
	t_mapObj2->position->y = -38;
	t_mapObj2->rotation->z = 180;
	gameObjects["mapObject02"] = mapObj2;
	
	// kamen
	MapObject * mapObj3 = new MapObject("resources/map/kamen.mdl");
	Transform * t_mapObj3 = (Transform*)mapObj3->getComponentById("transform");
	t_mapObj3->scale->x = 0.5;
	t_mapObj3->scale->y = 0.5;
	t_mapObj3->scale->z = 0.5;
	t_mapObj3->position->x = 10;
	t_mapObj3->position->y = -38;
	gameObjects["mapObject03"] = mapObj3;
	
	// oil_barrel
	MapObject * mapObj4 = new MapObject("resources/map/oil_barrel_m1.mdl");
	Transform * t_mapObj4 = (Transform*)mapObj4->getComponentById("transform");
	t_mapObj4->scale->x = 0.06;
	t_mapObj4->scale->y = 0.06;
	t_mapObj4->scale->z = 0.06;
	t_mapObj4->position->x = 35;
	t_mapObj4->position->y = -48;
	gameObjects["mapObject04"] = mapObj4;

	// christmas_tree
	MapObject * mapObj5 = new MapObject("resources/map/christmastree.mdl");
	Transform * t_mapObj5 = (Transform*)mapObj5->getComponentById("transform");
	t_mapObj5->scale->x = 0.05;
	t_mapObj5->scale->y = 0.05;
	t_mapObj5->scale->z = 0.05;
	t_mapObj5->position->x = 10;
	t_mapObj5->position->y = -24;
	gameObjects["mapObject05"] = mapObj5;

	// skeleton
	MapObject * mapObj6 = new MapObject("resources/map/skeleton.mdl");
	Transform * t_mapObj6 = (Transform*)mapObj6->getComponentById("transform");
	t_mapObj6->scale->x = 0.05;
	t_mapObj6->scale->y = 0.05;
	t_mapObj6->scale->z = 0.05;
	t_mapObj6->position->x = -40;
	t_mapObj6->position->y = 35;
	gameObjects["mapObject06"] = mapObj6;

	// train (1)
	MapObject * mapObj7 = new MapObject("resources/map/guterwagen.mdl");
	Transform * t_mapObj7 = (Transform*)mapObj7->getComponentById("transform");
	t_mapObj7->scale->x = 0.07;
	t_mapObj7->scale->y = 0.07;
	t_mapObj7->scale->z = 0.07;
	t_mapObj7->position->x = -38;
	t_mapObj7->position->y = 15;
	gameObjects["mapObject07"] = mapObj7;

	// train (2)
	MapObject * mapObj8 = new MapObject("resources/map/hbtest.mdl");
	Transform * t_mapObj8 = (Transform*)mapObj8->getComponentById("transform");
	t_mapObj8->scale->x = 0.07;
	t_mapObj8->scale->y = 0.07;
	t_mapObj8->scale->z = 0.07;
	t_mapObj8->position->x = -16;
	t_mapObj8->position->y = 15;
	gameObjects["mapObject08"] = mapObj8;

	// sandbags (1)
	MapObject * mapObj9 = new MapObject("resources/map/sandbags.mdl");
	Transform * t_mapObj9 = (Transform*)mapObj9->getComponentById("transform");
	t_mapObj9->scale->x = 0.05;
	t_mapObj9->scale->y = 0.05;
	t_mapObj9->scale->z = 0.05;
	t_mapObj9->position->x = 6;
	t_mapObj9->position->y = -24;
	gameObjects["mapObject09"] = mapObj9;

	// pc_MobileOffice (1)
	MapObject * mapObj10 = new MapObject("resources/map/pc_MobileOffice.mdl");
	Transform * t_mapObj10 = (Transform*)mapObj10->getComponentById("transform");
	t_mapObj10->scale->x = 0.05;
	t_mapObj10->scale->y = 0.05;
	t_mapObj10->scale->z = 0.05;
	t_mapObj10->position->x = -18;
	t_mapObj10->position->y = -40;
	t_mapObj10->rotation->z = 90;
	gameObjects["mapObject10"] = mapObj10;

	// AA_RangeTower_Height2_KN_Smesh
	MapObject * mapObj11 = new MapObject("resources/map/AA_RangeTower_Height2_KN_Smesh.mdl");
	Transform * t_mapObj11 = (Transform*)mapObj11->getComponentById("transform");
	t_mapObj11->scale->x = 0.05;
	t_mapObj11->scale->y = 0.05;
	t_mapObj11->scale->z = 0.05;
	t_mapObj11->position->x = 8;
	t_mapObj11->position->y = -45;
	gameObjects["mapObject11"] = mapObj11;

	// sandbags (2)
	MapObject * mapObj12 = new MapObject("resources/map/sandbags.mdl");
	Transform * t_mapObj12 = (Transform*)mapObj12->getComponentById("transform");
	t_mapObj12->scale->x = 0.05;
	t_mapObj12->scale->y = 0.05;
	t_mapObj12->scale->z = 0.05;
	t_mapObj12->position->x = 8;
	t_mapObj12->position->y = -24;
	gameObjects["mapObject12"] = mapObj12;

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
	gameObjects["mapObject13"] = mapObj13;

	// AF_tent_military
	MapObject * mapObj14 = new MapObject("resources/map/AF_tent_military.mdl");
	Transform * t_mapObj14 = (Transform*)mapObj14->getComponentById("transform");
	t_mapObj14->scale->x = 0.05;
	t_mapObj14->scale->y = 0.05;
	t_mapObj14->scale->z = 0.05;
	t_mapObj14->position->x = -40;
	t_mapObj14->position->y = 35;
	gameObjects["mapObject14"] = mapObj14;

	// AF_outdoors_kiosk
	MapObject * mapObj15 = new MapObject("resources/map/AF_outdoors_kiosk.mdl");
	Transform * t_mapObj15 = (Transform*)mapObj15->getComponentById("transform");
	t_mapObj15->scale->x = 0.05;
	t_mapObj15->scale->y = 0.05;
	t_mapObj15->scale->z = 0.05;
	t_mapObj15->position->x = 8;
	t_mapObj15->position->y = -30;
	gameObjects["mapObject15"] = mapObj15;

	// AA_Tent
	MapObject * mapObj16 = new MapObject("resources/map/AA_Tent.mdl");
	Transform * t_mapObj16 = (Transform*)mapObj16->getComponentById("transform");
	t_mapObj16->scale->x = 0.05;
	t_mapObj16->scale->y = 0.05;
	t_mapObj16->scale->z = 0.05;
	t_mapObj16->position->x = -42;
	t_mapObj16->position->y = -30;
	gameObjects["mapObject16"] = mapObj16;

	// pc_MobileOffice (2)
	MapObject * mapObj17 = new MapObject("resources/map/pc_MobileOffice.mdl");
	Transform * t_mapObj17 = (Transform*)mapObj17->getComponentById("transform");
	t_mapObj17->scale->x = 0.05;
	t_mapObj17->scale->y = 0.05;
	t_mapObj17->scale->z = 0.05;
	t_mapObj17->position->x = -18;
	t_mapObj17->position->y = -25;
	t_mapObj17->rotation->z = 90;
	gameObjects["mapObject17"] = mapObj17;

	// pc_MobileOffice (3)
	MapObject * mapObj18 = new MapObject("resources/map/pc_MobileOffice.mdl");
	Transform * t_mapObj18 = (Transform*)mapObj18->getComponentById("transform");
	t_mapObj18->scale->x = 0.05;
	t_mapObj18->scale->y = 0.05;
	t_mapObj18->scale->z = 0.05;
	t_mapObj18->position->x = -18;
	t_mapObj18->position->y = -10;
	t_mapObj18->rotation->z = 90;
	gameObjects["mapObject18"] = mapObj18;

	// pc_MobileOffice (4)
	MapObject * mapObj19 = new MapObject("resources/map/pc_MobileOffice.mdl");
	Transform * t_mapObj19 = (Transform*)mapObj19->getComponentById("transform");
	t_mapObj19->scale->x = 0.05;
	t_mapObj19->scale->y = 0.05;
	t_mapObj19->scale->z = 0.05;
	t_mapObj19->position->x = -33;
	t_mapObj19->position->y = -7;
	t_mapObj19->rotation->z = 180;
	gameObjects["mapObject19"] = mapObj19;

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
	
	((Player*)gameObjects["player"])->draw();
	//((Wall*)gameObjects["wall1"])->draw();	
	((Tower*)gameObjects["tower"])->draw();
	((Plane*)gameObjects["plane01"])->draw();
	
	((MapObject*)gameObjects["mapObject01"])->draw();
	((MapObject*)gameObjects["mapObject02"])->draw();
	((MapObject*)gameObjects["mapObject03"])->draw();
	((MapObject*)gameObjects["mapObject04"])->draw();
	((MapObject*)gameObjects["mapObject05"])->draw();
	((MapObject*)gameObjects["mapObject06"])->draw();
	((MapObject*)gameObjects["mapObject07"])->draw();
	((MapObject*)gameObjects["mapObject08"])->draw();
	((MapObject*)gameObjects["mapObject09"])->draw();
	((MapObject*)gameObjects["mapObject10"])->draw();
	((MapObject*)gameObjects["mapObject11"])->draw();
	((MapObject*)gameObjects["mapObject12"])->draw();
	((MapObject*)gameObjects["mapObject13"])->draw();
	((MapObject*)gameObjects["mapObject14"])->draw();
	((MapObject*)gameObjects["mapObject15"])->draw();
	((MapObject*)gameObjects["mapObject16"])->draw();
	((MapObject*)gameObjects["mapObject17"])->draw();
	((MapObject*)gameObjects["mapObject18"])->draw();
	((MapObject*)gameObjects["mapObject19"])->draw();

	level.draw();

	for (std::map<std::string, GameObject*>::iterator it1 = gameObjects.begin(); it1 != gameObjects.end(); ++it1)
	{
		GameObject * obj = it1->second;
		obj->draw();
	}


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
	Application::instance()->getTextures()->registerTexture("metal_plate", "resources/metal_plate.jpg");
	Application::instance()->getTextures()->registerTexture("rock_floor", "resources/rock_floor.jpg");
	Application::instance()->getTextures()->registerTexture("snow", "resources/snow.jpg");
	Application::instance()->getTextures()->registerTexture("snow_ice", "resources/snow_ice.jpg");
	Application::instance()->getTextures()->registerTexture("floor", "resources/floor.jpg");
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
