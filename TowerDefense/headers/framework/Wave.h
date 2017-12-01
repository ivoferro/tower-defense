#pragma once

#include <time.h>
#include <list>
#include "Drawable.h"
#include "Scene.h"
#include "../components/Transform.h"

class Wave
{

public:
	class WaveEnemy
	{
	public:
		WaveEnemy(std::string objectKey, Drawable * obj, int spawnSeconds);
		~WaveEnemy();

		std::string objectKey;
		Drawable * obj;
		int spawnSeconds;
	};

private:
	std::list<WaveEnemy*> enemies;
	std::list<WaveEnemy*> enemiesSpawned;
	std::list<WaveEnemy*> enemiesDead;
	time_t timer;
	Scene * scene;

	static size_t idGenerator;

public:
	Wave(Scene * scene);
	~Wave();
	void addEnemy(WaveEnemy * e);
	void timerActions();
	void spawnEnemies();
	void drawEnemies();
	void begin();

	int enemiesLeft;

};