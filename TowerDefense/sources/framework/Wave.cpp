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
		(*it)->~Enemy();
		scene->removeGameObject((GameObject*)((*it)->obj));
	}
	for (std::list<Enemy*>::iterator it = enemiesSpawned.begin(); it != enemiesSpawned.end(); ++it)
	{
		(*it)->~Enemy();
		scene->removeGameObject((GameObject*)((*it)->obj));
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
		int currentSeconds = (clock() - timer) / CLOCKS_PER_SEC;
		if (e->spawnSeconds >= currentSeconds)
		{
			enemies.remove(e);
			enemiesSpawned.push_back(e);

			GameObject * enemyGameObject = (GameObject*)(e->obj);

			// Why is it not working? when we add to the main scene
			// gameobjects map, it works... But when we try to read
			// from the map, there is a "read access violatione"
			// exception thrown...
			//scene->addGameObject(enemyGameObject);
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