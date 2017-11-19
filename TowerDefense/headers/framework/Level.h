#pragma once

#include <list>
#include "Wave.h"

class Level
{

public:
	enum Phase
	{
		BEGIN,
		COMBAT,
		WAVE_CLEAR,
		VICTORY,
		DEFEAT
	};

private:
	std::list<Wave*> waves;
	Phase phase;

public:
	Level();
	~Level();

	void addWave(Wave * wave);

	virtual void startNextWave() = 0;
	virtual void clearCurrentWave() = 0;

};