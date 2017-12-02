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
	setWave03();
}

Level01::~Level01()
{
}

void Level01::setWave01()
{
	Wave * wave01 = new Wave(scene);

	Enemy * e1 = new Enemy();
	Transform * e1T = (Transform*)e1->getComponentById("transform");
	e1T->position->x = -45;
	e1T->position->y = -45;
	e1T->position->z = 1;
	TargetPath * tp1 = (TargetPath*)e1->getComponentById("targetPath");
	tp1->addObjective(new Transform::Coordinates(-27.0f, -45.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-27.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, 0.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-2.0f, 0.0f, 0.0f));
	std::string e1Key = scene->addToWaitingObjects(e1);
	Wave::WaveEnemy * enemy01 = new Wave::WaveEnemy(e1Key, (Drawable*)e1, 0);

	Enemy * e2 = new Enemy();
	Transform * e2T = (Transform*)e2->getComponentById("transform");
	e2T->position->x = 45;
	e2T->position->y = 40;
	e2T->position->z = 1;
	TargetPath * tp2 = (TargetPath*)e2->getComponentById("targetPath");
	tp2->addObjective(new Transform::Coordinates(40.0f, 15.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(30.0f, 0.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(2.0f, 0.0f, 0.0f));
	std::string e2Key = scene->addToWaitingObjects(e2);
	Wave::WaveEnemy * enemy02 = new Wave::WaveEnemy(e2Key, (Drawable*)e2, 0);

	wave01->addEnemy(enemy01);
	wave01->addEnemy(enemy02);
	addWave(wave01);
}

void Level01::setWave02()
{
	Wave * wave02 = new Wave(scene);

	Enemy * e1 = new Enemy();
	Transform * e1T = (Transform*)e1->getComponentById("transform");
	e1T->position->x = -45;
	e1T->position->y = -45;
	e1T->position->z = 1;
	TargetPath * tp1 = (TargetPath*)e1->getComponentById("targetPath");
	tp1->addObjective(new Transform::Coordinates(-27.0f, -45.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-27.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, 0.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-2.0f, 0.0f, 0.0f));
	std::string e1Key = scene->addToWaitingObjects(e1);
	Wave::WaveEnemy * enemy01 = new Wave::WaveEnemy(e1Key, (Drawable*)e1, 0);

	Enemy * e2 = new Enemy();
	Transform * e2T = (Transform*)e2->getComponentById("transform");
	e2T->position->x = 45;
	e2T->position->y = 40;
	e2T->position->z = 1;
	TargetPath * tp2 = (TargetPath*)e2->getComponentById("targetPath");
	tp2->addObjective(new Transform::Coordinates(40.0f, 15.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(30.0f, 0.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(2.0f, 0.0f, 0.0f));
	std::string e2Key = scene->addToWaitingObjects(e2);
	Wave::WaveEnemy * enemy02 = new Wave::WaveEnemy(e2Key, (Drawable*)e2, 0);

	Enemy * e3 = new Enemy();
	Transform * e3T = (Transform*)e3->getComponentById("transform");
	e3T->position->x = -45;
	e3T->position->y = 23;
	e3T->position->z = 1;
	TargetPath * tp3 = (TargetPath*)e3->getComponentById("targetPath");
	tp3->addObjective(new Transform::Coordinates(-30.0f, 23.0f, 0.0f));
	tp3->addObjective(new Transform::Coordinates(-3.0f, 40.0f, 0.0f));
	tp3->addObjective(new Transform::Coordinates(0.0f, 2.0f, 0.0f));
	std::string e3Key = scene->addToWaitingObjects(e3);
	Wave::WaveEnemy * enemy03 = new Wave::WaveEnemy(e3Key, (Drawable*)e3, 10);

	Enemy * e4 = new Enemy();
	Transform * e4T = (Transform*)e4->getComponentById("transform");
	e4T->position->x = 0;
	e4T->position->y = -45;
	e4T->position->z = 1;
	TargetPath * tp4 = (TargetPath*)e4->getComponentById("targetPath");
	tp4->addObjective(new Transform::Coordinates(-10.0f, -45.0f, 0.0f));
	tp4->addObjective(new Transform::Coordinates(-10.0f, -25.0f, 0.0f));
	tp4->addObjective(new Transform::Coordinates(0.0f, -2.0f, 0.0f));
	std::string e4Key = scene->addToWaitingObjects(e4);
	Wave::WaveEnemy * enemy04 = new Wave::WaveEnemy(e4Key, (Drawable*)e4, 10);

	wave02->addEnemy(enemy01);
	wave02->addEnemy(enemy02);
	wave02->addEnemy(enemy03);
	wave02->addEnemy(enemy04);
	addWave(wave02);
}

void Level01::setWave03()
{
	Wave * wave03 = new Wave(scene);

	Enemy * e1 = new Enemy();
	Transform * e1T = (Transform*)e1->getComponentById("transform");
	e1T->position->x = -45;
	e1T->position->y = -45;
	e1T->position->z = 1;
	TargetPath * tp1 = (TargetPath*)e1->getComponentById("targetPath");
	tp1->addObjective(new Transform::Coordinates(-27.0f, -45.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-27.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, 0.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-2.0f, 0.0f, 0.0f));
	std::string e1Key = scene->addToWaitingObjects(e1);
	Wave::WaveEnemy * enemy01 = new Wave::WaveEnemy(e1Key, (Drawable*)e1, 0);

	Enemy * e2 = new Enemy();
	Transform * e2T = (Transform*)e2->getComponentById("transform");
	e2T->position->x = 45;
	e2T->position->y = 40;
	e2T->position->z = 1;
	TargetPath * tp2 = (TargetPath*)e2->getComponentById("targetPath");
	tp2->addObjective(new Transform::Coordinates(40.0f, 15.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(30.0f, 0.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(2.0f, 0.0f, 0.0f));
	std::string e2Key = scene->addToWaitingObjects(e2);
	Wave::WaveEnemy * enemy02 = new Wave::WaveEnemy(e2Key, (Drawable*)e2, 0);

	Enemy * e3 = new Enemy();
	Transform * e3T = (Transform*)e3->getComponentById("transform");
	e3T->position->x = -45;
	e3T->position->y = 23;
	e3T->position->z = 1;
	TargetPath * tp3 = (TargetPath*)e3->getComponentById("targetPath");
	tp3->addObjective(new Transform::Coordinates(-30.0f, 23.0f, 0.0f));
	tp3->addObjective(new Transform::Coordinates(-3.0f, 40.0f, 0.0f));
	tp3->addObjective(new Transform::Coordinates(0.0f, 2.0f, 0.0f));
	std::string e3Key = scene->addToWaitingObjects(e3);
	Wave::WaveEnemy * enemy03 = new Wave::WaveEnemy(e3Key, (Drawable*)e3, 0);

	Enemy * e4 = new Enemy();
	Transform * e4T = (Transform*)e4->getComponentById("transform");
	e4T->position->x = 0;
	e4T->position->y = -45;
	e4T->position->z = 1;
	TargetPath * tp4 = (TargetPath*)e4->getComponentById("targetPath");
	tp4->addObjective(new Transform::Coordinates(-10.0f, -45.0f, 0.0f));
	tp4->addObjective(new Transform::Coordinates(-10.0f, -25.0f, 0.0f));
	tp4->addObjective(new Transform::Coordinates(0.0f, -2.0f, 0.0f));
	std::string e4Key = scene->addToWaitingObjects(e4);
	Wave::WaveEnemy * enemy04 = new Wave::WaveEnemy(e4Key, (Drawable*)e4, 0);

	wave03->addEnemy(enemy01);
	wave03->addEnemy(enemy02);
	wave03->addEnemy(enemy03);
	wave03->addEnemy(enemy04);
	addWave(wave03);
}
