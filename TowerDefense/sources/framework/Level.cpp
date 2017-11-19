#include "../../headers/framework/Level.h"

Level::Level()
{
	phase = INITIAL;
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
		// TODO manage game objects from scene
		currentWave->begin();
		phase = Phase::COMBAT;
	}
}

void Level::clearCurrentWave()
{
	if (phase == Phase::COMBAT)
	{
		Wave * currentWave = waves.front();
		// TODO manage game objects from scene
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
	// TODO tell wave to draw itself
}