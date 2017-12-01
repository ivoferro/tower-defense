#include "../../headers/framework/Level.h"

Level::Level(Scene * scene)
{
	phase = INITIAL;
	this->scene = scene;
}

Level::~Level()
{
	for (std::list<Wave*>::iterator it = waves.begin(); it != waves.end(); ++it)
	{
		(*it)->~Wave();
	}
}

void Level::addWave(Wave * wave)
{
	waves.push_back(wave);
}

void Level::startNextWave()
{
	if (waves.size() > 0)
	{
		Wave * currentWave = waves.front();
		currentWave->begin();
		phase = Phase::COMBAT;
	}
}

void Level::clearCurrentWave()
{
	if (phase == Phase::COMBAT)
	{
		Wave * currentWave = waves.front();
		currentWave->~Wave();
		waves.pop_front();

		if (waves.size() > 0)
		{
			phase = Phase::WAVE_CLEAR;
		}
		else
		{
			phase = Phase::VICTORY;
		}
	}
}

void Level::draw()
{
	if (phase == Phase::COMBAT)
	{
		Wave * currentWave = waves.front();
		currentWave->drawEnemies();
	}
}

void Level::timerActions()
{
	if (phase == Phase::COMBAT)
	{
		Wave * currentWave = waves.front();
		currentWave->timerActions();

		if (currentWave->enemiesLeft <= 0)
		{
			printf("Wave clear");
			clearCurrentWave();
		}
	}
}
