#include "..\..\headers\framework\Wave.h"

Wave::Wave()
{
	enemiesLeft = 0;
}

Wave::~Wave()
{
	for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		(*it)->~Enemy();
	}
	for (std::list<Enemy*>::iterator it = enemiesSpawned.begin(); it != enemiesSpawned.end(); ++it)
	{
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
	for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		Enemy *e = *it;
		int currentSeconds = (clock() - timer) / CLOCKS_PER_SEC;
		if (e->spawnSeconds >= currentSeconds)
		{
			enemies.remove(e);
			enemiesSpawned.push_back(e);
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
	timer = clock();
}

Wave::Enemy::Enemy(Drawable * obj, int spawnSeconds)
{
	this->obj = obj;
	this->spawnSeconds = spawnSeconds;
}

Wave::Enemy::~Enemy()
{
	obj->~Drawable();
}