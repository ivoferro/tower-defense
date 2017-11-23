#pragma once

#include <list>
#include "Wave.h"
#include "Scene.h"

class Level
{

public:
	enum Phase
	{
		INITIAL,
		COMBAT,
		WAVE_CLEAR,
		VICTORY,
		DEFEAT
	};

private:
	std::list<Wave*> waves;
	Phase phase;

protected:
	Scene * scene;

public:
	Level(Scene * scene);
	~Level();

	void addWave(Wave * wave);

	void startNextWave();

	void clearCurrentWave();

	void draw();

	void timerActions();

};