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
		Enemy(std::string objectKey, Drawable * obj, int spawnSeconds);
		~Enemy();

		std::string objectKey;
		Drawable * obj;
		int spawnSeconds;
	};

private:
	std::list<Enemy*> enemies;
	std::list<Enemy*> enemiesSpawned;
	clock_t timer;
	int enemiesLeft;
	Scene * scene;

	static size_t idGenerator;

public:
	Wave(Scene * scene);
	~Wave();
	void addEnemy(Enemy * e);
	void spawnEnemies();
	void drawEnemies();
	void begin();

};