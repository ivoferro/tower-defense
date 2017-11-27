#include "../../headers/levels/Level01.h"
#include "../../headers/framework/Wave.h"
#include "../../headers/framework/Drawable.h"
#include "../../headers/gameobjects/Enemy.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/TargetPath.h"

Level01::Level01(Scene * scene) : Level(scene)
{
	setWave01();
	setWave02();
}

Level01::~Level01()
{
}

void Level01::setWave01()
{
	Wave * wave01 = new Wave(scene);

	Enemy * e1 = new Enemy();
	Transform * e1T = (Transform*)e1->getComponentById("transform");
	e1T->position->x = -25;
	e1T->position->y = -25;
	e1T->position->z = 1;
	TargetPath * targetPath = (TargetPath*)e1->getComponentById("targetPath");
	std::string e1Key = scene->addToWaitingObjects(e1);
	targetPath->addObjective(new Transform::Coordinates(20.0f, -20.0f, 0.0f));
	targetPath->addObjective(new Transform::Coordinates(15.0f, 10.0f, 0.0f));
	targetPath->addObjective(new Transform::Coordinates(0.0f, 0.0f, 0.0f));
	Wave::Enemy * enemy01 = new Wave::Enemy(e1Key, (Drawable*)e1, 0);

	Enemy * e2 = new Enemy();
	Transform * e2T = (Transform*)e2->getComponentById("transform");
	e2T->position->x = 20;
	e2T->position->y = 20;
	e2T->position->z = 1;
	std::string e2Key = scene->addToWaitingObjects(e2);
	Wave::Enemy * enemy02 = new Wave::Enemy(e2Key, (Drawable*)e2, 0);

	wave01->addEnemy(enemy01);
	wave01->addEnemy(enemy02);
	addWave(wave01);
}

void Level01::setWave02()
{
	Wave * wave02 = new Wave(scene);

	Enemy * e1 = new Enemy();
	Transform * e1T = (Transform*)e1->getComponentById("transform");
	e1T->position->x = -20;
	e1T->position->y = -20;
	e1T->position->z = 1;
	std::string e1Key = scene->addToWaitingObjects(e1);
	Wave::Enemy * enemy01 = new Wave::Enemy(e1Key, (Drawable*)e1, 0);

	Enemy * e2 = new Enemy();
	Transform * e2T = (Transform*)e2->getComponentById("transform");
	e2T->position->x = 20;
	e2T->position->y = 20;
	e2T->position->z = 1;
	std::string e2Key = scene->addToWaitingObjects(e2);
	Wave::Enemy * enemy02 = new Wave::Enemy(e2Key, (Drawable*)e2, 0);

	Enemy * e3 = new Enemy();
	Transform * e3T = (Transform*)e3->getComponentById("transform");
	e3T->position->x = 0;
	e3T->position->y = 20;
	e3T->position->z = 1;
	std::string e3Key = scene->addToWaitingObjects(e3);
	Wave::Enemy * enemy03 = new Wave::Enemy(e3Key, (Drawable*)e3, 10);

	Enemy * e4 = new Enemy();
	Transform * e4T = (Transform*)e4->getComponentById("transform");
	e4T->position->x = 20;
	e4T->position->y = 0;
	e4T->position->z = 1;
	std::string e4Key = scene->addToWaitingObjects(e4);
	Wave::Enemy * enemy04 = new Wave::Enemy(e4Key, (Drawable*)e4, 10);

	wave02->addEnemy(enemy01);
	wave02->addEnemy(enemy02);
	wave02->addEnemy(enemy03);
	wave02->addEnemy(enemy04);
	addWave(wave02);
}