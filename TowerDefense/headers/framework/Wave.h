#pragma once

#include <time.h>
#include <list>
#include "Drawable.h"
#include "Scene.h"
#include "../components/Transform.h"

class Wave
{

public:
	class Enemy
	{
	public:
		Enemy(Drawable * obj, Transform * spawnPos, int spawnSeconds);
		~Enemy();
		Drawable * obj;
		Transform * spawnPos;
		int spawnSeconds;
	};

private:
	std::list<Enemy*> enemies;
	std::list<Enemy*> enemiesSpawned;
	clock_t timer;
	int enemiesLeft;

public:
	Wave();
	~Wave();
	void addEnemy(Enemy * e);
	void spawnEnemies();
	void drawEnemies();
	void begin();

};