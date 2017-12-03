#pragma once

#include "../framework/Level.h"

class Level01 : public Level
{

private:
	void setWave01();
	void setWave02();
	void setWave03();
	void setWave04();
	void setWave05();

public:
	Level01(Scene * scene);
	~Level01();

};

