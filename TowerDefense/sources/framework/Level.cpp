#include "../../headers/framework/Level.h"

Level::Level()
{
	phase = BEGIN;
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