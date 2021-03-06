#include "../../headers/levels/Level01.h"
#include "../../headers/framework/Wave.h"
#include "../../headers/framework/Drawable.h"
#include "../../headers/gameobjects/Enemy.h"
#include "../../headers/gameobjects/Boss.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/TargetPath.h"

Level01::Level01(Scene * scene) : Level(scene)
{
	setWave01();
	setWave02();
	setWave03();
	setWave04();
	setWave05();
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
	e1T->position->z = 2;
	TargetPath * tp1 = (TargetPath*)e1->getComponentById("targetPath");
	tp1->addObjective(new Transform::Coordinates(-27.0f, -45.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-27.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, 0.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-1.0f, 0.0f, 0.0f));
	std::string e1Key = scene->addToWaitingObjects(e1);
	Wave::WaveEnemy * enemy01 = new Wave::WaveEnemy(e1Key, (Drawable*)e1, 0);

	Enemy * e2 = new Enemy();
	Transform * e2T = (Transform*)e2->getComponentById("transform");
	e2T->position->x = 45;
	e2T->position->y = 40;
	e2T->position->z = 2;
	TargetPath * tp2 = (TargetPath*)e2->getComponentById("targetPath");
	tp2->addObjective(new Transform::Coordinates(40.0f, 15.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(30.0f, 0.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(1.0f, 0.0f, 0.0f));
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
	e1T->position->z = 2;
	TargetPath * tp1 = (TargetPath*)e1->getComponentById("targetPath");
	tp1->addObjective(new Transform::Coordinates(-27.0f, -45.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-27.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, 0.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-1.0f, 0.0f, 0.0f));
	std::string e1Key = scene->addToWaitingObjects(e1);
	Wave::WaveEnemy * enemy01 = new Wave::WaveEnemy(e1Key, (Drawable*)e1, 0);

	Enemy * e2 = new Enemy();
	Transform * e2T = (Transform*)e2->getComponentById("transform");
	e2T->position->x = 45;
	e2T->position->y = 40;
	e2T->position->z = 2;
	TargetPath * tp2 = (TargetPath*)e2->getComponentById("targetPath");
	tp2->addObjective(new Transform::Coordinates(40.0f, 15.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(30.0f, 0.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(1.0f, 0.0f, 0.0f));
	std::string e2Key = scene->addToWaitingObjects(e2);
	Wave::WaveEnemy * enemy02 = new Wave::WaveEnemy(e2Key, (Drawable*)e2, 0);

	Enemy * e3 = new Enemy();
	Transform * e3T = (Transform*)e3->getComponentById("transform");
	e3T->position->x = -45;
	e3T->position->y = 23;
	e3T->position->z = 2;
	TargetPath * tp3 = (TargetPath*)e3->getComponentById("targetPath");
	tp3->addObjective(new Transform::Coordinates(-30.0f, 23.0f, 0.0f));
	tp3->addObjective(new Transform::Coordinates(-3.0f, 40.0f, 0.0f));
	tp3->addObjective(new Transform::Coordinates(0.0f, 1.0f, 0.0f));
	std::string e3Key = scene->addToWaitingObjects(e3);
	Wave::WaveEnemy * enemy03 = new Wave::WaveEnemy(e3Key, (Drawable*)e3, 10);

	Enemy * e4 = new Enemy();
	Transform * e4T = (Transform*)e4->getComponentById("transform");
	e4T->position->x = 0;
	e4T->position->y = -45;
	e4T->position->z = 2;
	TargetPath * tp4 = (TargetPath*)e4->getComponentById("targetPath");
	tp4->addObjective(new Transform::Coordinates(-10.0f, -45.0f, 0.0f));
	tp4->addObjective(new Transform::Coordinates(-10.0f, -25.0f, 0.0f));
	tp4->addObjective(new Transform::Coordinates(0.0f, -1.0f, 0.0f));
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
	e1T->position->z = 2;
	TargetPath * tp1 = (TargetPath*)e1->getComponentById("targetPath");
	tp1->addObjective(new Transform::Coordinates(-27.0f, -45.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-27.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, 0.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-1.0f, 0.0f, 0.0f));
	std::string e1Key = scene->addToWaitingObjects(e1);
	Wave::WaveEnemy * enemy01 = new Wave::WaveEnemy(e1Key, (Drawable*)e1, 0);

	Enemy * e2 = new Enemy();
	Transform * e2T = (Transform*)e2->getComponentById("transform");
	e2T->position->x = 45;
	e2T->position->y = 40;
	e2T->position->z = 2;
	TargetPath * tp2 = (TargetPath*)e2->getComponentById("targetPath");
	tp2->addObjective(new Transform::Coordinates(40.0f, 15.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(30.0f, 0.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(1.0f, 0.0f, 0.0f));
	std::string e2Key = scene->addToWaitingObjects(e2);
	Wave::WaveEnemy * enemy02 = new Wave::WaveEnemy(e2Key, (Drawable*)e2, 0);

	Enemy * e3 = new Enemy();
	Transform * e3T = (Transform*)e3->getComponentById("transform");
	e3T->position->x = -45;
	e3T->position->y = 23;
	e3T->position->z = 2;
	TargetPath * tp3 = (TargetPath*)e3->getComponentById("targetPath");
	tp3->addObjective(new Transform::Coordinates(-30.0f, 23.0f, 0.0f));
	tp3->addObjective(new Transform::Coordinates(-3.0f, 40.0f, 0.0f));
	tp3->addObjective(new Transform::Coordinates(0.0f, 1.0f, 0.0f));
	std::string e3Key = scene->addToWaitingObjects(e3);
	Wave::WaveEnemy * enemy03 = new Wave::WaveEnemy(e3Key, (Drawable*)e3, 0);

	Enemy * e4 = new Enemy();
	Transform * e4T = (Transform*)e4->getComponentById("transform");
	e4T->position->x = 0;
	e4T->position->y = -45;
	e4T->position->z = 2;
	TargetPath * tp4 = (TargetPath*)e4->getComponentById("targetPath");
	tp4->addObjective(new Transform::Coordinates(-10.0f, -45.0f, 0.0f));
	tp4->addObjective(new Transform::Coordinates(-10.0f, -25.0f, 0.0f));
	tp4->addObjective(new Transform::Coordinates(0.0f, -1.0f, 0.0f));
	std::string e4Key = scene->addToWaitingObjects(e4);
	Wave::WaveEnemy * enemy04 = new Wave::WaveEnemy(e4Key, (Drawable*)e4, 0);

	wave03->addEnemy(enemy01);
	wave03->addEnemy(enemy02);
	wave03->addEnemy(enemy03);
	wave03->addEnemy(enemy04);
	addWave(wave03);
}

void Level01::setWave04()
{
	Wave * wave04 = new Wave(scene);

	Enemy * e1 = new Enemy();
	Transform * e1T = (Transform*)e1->getComponentById("transform");
	e1T->position->x = -45;
	e1T->position->y = -45;
	e1T->position->z = 2;
	TargetPath * tp1 = (TargetPath*)e1->getComponentById("targetPath");
	tp1->addObjective(new Transform::Coordinates(-27.0f, -45.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-27.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, 0.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-1.0f, 0.0f, 0.0f));
	std::string e1Key = scene->addToWaitingObjects(e1);
	Wave::WaveEnemy * enemy01 = new Wave::WaveEnemy(e1Key, (Drawable*)e1, 0);

	Enemy * e2 = new Enemy();
	Transform * e2T = (Transform*)e2->getComponentById("transform");
	e2T->position->x = 45;
	e2T->position->y = 40;
	e2T->position->z = 2;
	TargetPath * tp2 = (TargetPath*)e2->getComponentById("targetPath");
	tp2->addObjective(new Transform::Coordinates(40.0f, 15.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(30.0f, 0.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(1.0f, 0.0f, 0.0f));
	std::string e2Key = scene->addToWaitingObjects(e2);
	Wave::WaveEnemy * enemy02 = new Wave::WaveEnemy(e2Key, (Drawable*)e2, 0);

	Enemy * e3 = new Enemy();
	Transform * e3T = (Transform*)e3->getComponentById("transform");
	e3T->position->x = -45;
	e3T->position->y = 23;
	e3T->position->z = 2;
	TargetPath * tp3 = (TargetPath*)e3->getComponentById("targetPath");
	tp3->addObjective(new Transform::Coordinates(-30.0f, 23.0f, 0.0f));
	tp3->addObjective(new Transform::Coordinates(-3.0f, 40.0f, 0.0f));
	tp3->addObjective(new Transform::Coordinates(0.0f, 1.0f, 0.0f));
	std::string e3Key = scene->addToWaitingObjects(e3);
	Wave::WaveEnemy * enemy03 = new Wave::WaveEnemy(e3Key, (Drawable*)e3, 0);

	Enemy * e4 = new Enemy();
	Transform * e4T = (Transform*)e4->getComponentById("transform");
	e4T->position->x = 0;
	e4T->position->y = -45;
	e4T->position->z = 2;
	TargetPath * tp4 = (TargetPath*)e4->getComponentById("targetPath");
	tp4->addObjective(new Transform::Coordinates(-10.0f, -45.0f, 0.0f));
	tp4->addObjective(new Transform::Coordinates(-10.0f, -25.0f, 0.0f));
	tp4->addObjective(new Transform::Coordinates(0.0f, -1.0f, 0.0f));
	std::string e4Key = scene->addToWaitingObjects(e4);
	Wave::WaveEnemy * enemy04 = new Wave::WaveEnemy(e4Key, (Drawable*)e4, 0);

	Enemy * e5 = new Enemy();
	Transform * e5T = (Transform*)e5->getComponentById("transform");
	e5T->position->x = 47;
	e5T->position->y = -47;
	e5T->position->z = 2;
	TargetPath * tp5 = (TargetPath*)e5->getComponentById("targetPath");
	tp5->addObjective(new Transform::Coordinates(47.0f, -5.0f, 0.0f));
	tp5->addObjective(new Transform::Coordinates(1.0f, -1.0f, 0.0f));
	std::string e5Key = scene->addToWaitingObjects(e5);
	Wave::WaveEnemy * enemy05 = new Wave::WaveEnemy(e5Key, (Drawable*)e5, 15);

	Enemy * e6 = new Enemy();
	Transform * e6T = (Transform*)e6->getComponentById("transform");
	e6T->position->x = 15;
	e6T->position->y = -47;
	e6T->position->z = 2;
	TargetPath * tp6 = (TargetPath*)e6->getComponentById("targetPath");
	tp6->addObjective(new Transform::Coordinates(15.0f, -10.0f, 0.0f));
	tp6->addObjective(new Transform::Coordinates(-1.0f, -1.0f, 0.0f));
	std::string e6Key = scene->addToWaitingObjects(e6);
	Wave::WaveEnemy * enemy06 = new Wave::WaveEnemy(e6Key, (Drawable*)e6, 15);

	wave04->addEnemy(enemy01);
	wave04->addEnemy(enemy02);
	wave04->addEnemy(enemy03);
	wave04->addEnemy(enemy04);
	wave04->addEnemy(enemy05);
	wave04->addEnemy(enemy06);
	addWave(wave04);
}

void Level01::setWave05()
{
	Wave * wave05 = new Wave(scene);

	Enemy * e1 = new Enemy();
	Transform * e1T = (Transform*)e1->getComponentById("transform");
	e1T->position->x = -45;
	e1T->position->y = -45;
	e1T->position->z = 2;
	TargetPath * tp1 = (TargetPath*)e1->getComponentById("targetPath");
	tp1->addObjective(new Transform::Coordinates(-27.0f, -45.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-27.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, -15.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-45.0f, 0.0f, 0.0f));
	tp1->addObjective(new Transform::Coordinates(-1.0f, 0.0f, 0.0f));
	std::string e1Key = scene->addToWaitingObjects(e1);
	Wave::WaveEnemy * enemy01 = new Wave::WaveEnemy(e1Key, (Drawable*)e1, 0);

	Enemy * e2 = new Enemy();
	Transform * e2T = (Transform*)e2->getComponentById("transform");
	e2T->position->x = 45;
	e2T->position->y = 40;
	e2T->position->z = 2;
	TargetPath * tp2 = (TargetPath*)e2->getComponentById("targetPath");
	tp2->addObjective(new Transform::Coordinates(40.0f, 15.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(30.0f, 0.0f, 0.0f));
	tp2->addObjective(new Transform::Coordinates(1.0f, 0.0f, 0.0f));
	std::string e2Key = scene->addToWaitingObjects(e2);
	Wave::WaveEnemy * enemy02 = new Wave::WaveEnemy(e2Key, (Drawable*)e2, 0);

	Enemy * e3 = new Enemy();
	Transform * e3T = (Transform*)e3->getComponentById("transform");
	e3T->position->x = -45;
	e3T->position->y = 23;
	e3T->position->z = 2;
	TargetPath * tp3 = (TargetPath*)e3->getComponentById("targetPath");
	tp3->addObjective(new Transform::Coordinates(-30.0f, 23.0f, 0.0f));
	tp3->addObjective(new Transform::Coordinates(-3.0f, 40.0f, 0.0f));
	tp3->addObjective(new Transform::Coordinates(0.0f, 1.0f, 0.0f));
	std::string e3Key = scene->addToWaitingObjects(e3);
	Wave::WaveEnemy * enemy03 = new Wave::WaveEnemy(e3Key, (Drawable*)e3, 0);

	Enemy * e4 = new Enemy();
	Transform * e4T = (Transform*)e4->getComponentById("transform");
	e4T->position->x = 0;
	e4T->position->y = -45;
	e4T->position->z = 2;
	TargetPath * tp4 = (TargetPath*)e4->getComponentById("targetPath");
	tp4->addObjective(new Transform::Coordinates(-10.0f, -45.0f, 0.0f));
	tp4->addObjective(new Transform::Coordinates(-10.0f, -25.0f, 0.0f));
	tp4->addObjective(new Transform::Coordinates(0.0f, -1.0f, 0.0f));
	std::string e4Key = scene->addToWaitingObjects(e4);
	Wave::WaveEnemy * enemy04 = new Wave::WaveEnemy(e4Key, (Drawable*)e4, 0);

	Enemy * e5 = new Enemy();
	Transform * e5T = (Transform*)e5->getComponentById("transform");
	e5T->position->x = 47;
	e5T->position->y = -47;
	e5T->position->z = 2;
	TargetPath * tp5 = (TargetPath*)e5->getComponentById("targetPath");
	tp5->addObjective(new Transform::Coordinates(47.0f, -5.0f, 0.0f));
	tp5->addObjective(new Transform::Coordinates(1.0f, -1.0f, 0.0f));
	std::string e5Key = scene->addToWaitingObjects(e5);
	Wave::WaveEnemy * enemy05 = new Wave::WaveEnemy(e5Key, (Drawable*)e5, 15);

	Enemy * e6 = new Enemy();
	Transform * e6T = (Transform*)e6->getComponentById("transform");
	e6T->position->x = 15;
	e6T->position->y = -47;
	e6T->position->z = 2;
	TargetPath * tp6 = (TargetPath*)e6->getComponentById("targetPath");
	tp6->addObjective(new Transform::Coordinates(15.0f, -10.0f, 0.0f));
	tp6->addObjective(new Transform::Coordinates(-1.0f, -1.0f, 0.0f));
	std::string e6Key = scene->addToWaitingObjects(e6);
	Wave::WaveEnemy * enemy06 = new Wave::WaveEnemy(e6Key, (Drawable*)e6, 15);

	Boss * boss = new Boss();
	Transform * bossT = (Transform*)boss->getComponentById("transform");
	bossT->position->x = -45;
	bossT->position->y = -45;
	bossT->position->z = 3.5;
	TargetPath * bossTp = (TargetPath*)boss->getComponentById("targetPath");
	bossTp->addObjective(new Transform::Coordinates(-27.0f, -45.0f, 0.0f));
	bossTp->addObjective(new Transform::Coordinates(-27.0f, -15.0f, 0.0f));
	bossTp->addObjective(new Transform::Coordinates(-45.0f, -15.0f, 0.0f));
	bossTp->addObjective(new Transform::Coordinates(-45.0f, 0.0f, 0.0f));
	bossTp->addObjective(new Transform::Coordinates(-1.0f, 0.0f, 0.0f));
	std::string bossKey = scene->addToWaitingObjects(boss);
	Wave::WaveEnemy * enemyBoss = new Wave::WaveEnemy(bossKey, (Drawable*)boss, 30);


	wave05->addEnemy(enemy01);
	wave05->addEnemy(enemy02);
	wave05->addEnemy(enemy03);
	wave05->addEnemy(enemy04);
	wave05->addEnemy(enemy05);
	wave05->addEnemy(enemy06);
	wave05->addEnemy(enemyBoss);
	addWave(wave05);
}
