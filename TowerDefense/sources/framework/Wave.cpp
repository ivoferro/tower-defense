#include "../../headers/framework/Wave.h"
#include "../../headers/gameobjects/Enemy.h"
#include "../../headers/gameobjects/Boss.h"

Wave::Wave(Scene * scene)
{
	this->scene = scene;
	enemiesLeft = 0;
}

Wave::~Wave()
{
	for (std::list<WaveEnemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		scene->removeGameObject((*it)->objectKey);
		(*it)->~WaveEnemy();
	}
	for (std::list<WaveEnemy*>::iterator it = enemiesSpawned.begin(); it != enemiesSpawned.end(); ++it)
	{
		scene->removeGameObject((*it)->objectKey);
		(*it)->~WaveEnemy();
	}
	for (std::list<WaveEnemy*>::iterator it = enemiesDead.begin(); it != enemiesDead.end(); ++it)
	{
		scene->removeGameObject((*it)->objectKey);
		(*it)->~WaveEnemy();
	}
}

void Wave::addEnemy(WaveEnemy * e)
{
	enemies.push_back(e);
	enemiesLeft++;
}

void Wave::timerActions()
{
	std::list<WaveEnemy*>::iterator it = enemiesSpawned.begin();

	spawnEnemies();

	while (it != enemiesSpawned.end()) {
		WaveEnemy *e = *(it++);

		if (Enemy * enemy = dynamic_cast<Enemy*>(e->obj))
		{
			if (!enemy->isAlive)
			{
				enemiesSpawned.remove(e);
				enemiesDead.push_back(e);
				enemiesLeft--;
			}
		}
		else if (Boss * boss = dynamic_cast<Boss*>(e->obj))
		{
			if (!boss->isAlive)
			{
				enemiesSpawned.remove(e);
				enemiesDead.push_back(e);
				enemiesLeft--;
			}
		}
	}
}

void Wave::spawnEnemies()
{
	std::list<WaveEnemy*>::iterator it = enemies.begin();
	while (it != enemies.end()) {
		WaveEnemy *e = *(it++);
		int currentSeconds = difftime(time(0), timer);
		if (e->spawnSeconds <= currentSeconds)
		{
			enemies.remove(e);
			enemiesSpawned.push_back(e);
			scene->activateObject(e->objectKey);
		}
	}
}

void Wave::drawEnemies()
{
	for (std::list<WaveEnemy*>::iterator it = enemiesSpawned.begin(); it != enemiesSpawned.end(); ++it)
	{
		WaveEnemy *e = *it;
		e->obj->draw();
	}
}

void Wave::begin()
{
	timer = time(0);
}

Wave::WaveEnemy::WaveEnemy(std::string objectKey, Drawable * obj, int spawnSeconds)
{
	this->objectKey = objectKey;
	this->obj = obj;
	this->spawnSeconds = spawnSeconds;
}

Wave::WaveEnemy::~WaveEnemy()
{
	obj->~Drawable();
}