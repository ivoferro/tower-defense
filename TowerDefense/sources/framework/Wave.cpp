#include "..\..\headers\framework\Wave.h"

Wave::Wave(Scene * scene)
{
	this->scene = scene;
	enemiesLeft = 0;
}

Wave::~Wave()
{
	for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		scene->removeGameObject((*it)->objectKey);
		(*it)->~Enemy();
	}
	for (std::list<Enemy*>::iterator it = enemiesSpawned.begin(); it != enemiesSpawned.end(); ++it)
	{
		scene->removeGameObject((*it)->objectKey);
		(*it)->~Enemy();
	}
}

void Wave::addEnemy(Enemy * e)
{
	enemies.push_back(e);
	enemiesLeft++;
}

void Wave::spawnEnemies()
{
	std::list<Enemy*>::iterator it = enemies.begin();
	while (it != enemies.end()) {
		Enemy *e = *(it++);
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
	for (std::list<Enemy*>::iterator it = enemiesSpawned.begin(); it != enemiesSpawned.end(); ++it)
	{
		Enemy *e = *it;
		e->obj->draw();
	}
}

void Wave::begin()
{
	timer = time(0);
}

Wave::Enemy::Enemy(std::string objectKey, Drawable * obj, int spawnSeconds)
{
	this->objectKey = objectKey;
	this->obj = obj;
	this->spawnSeconds = spawnSeconds;
}

Wave::Enemy::~Enemy()
{
	obj->~Drawable();
}