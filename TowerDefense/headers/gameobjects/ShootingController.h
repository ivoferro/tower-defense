#pragma once

#include "../framework/GameObject.h"
#include "../framework/Scene.h"
#include <time.h>

class ShootingController : public GameObject
{

private:
	Scene * parentScene;
	time_t timer;
	GLfloat cooldownSeconds;
	GLboolean isOnCooldown;
	void spawnBullet();

public:
	ShootingController(Scene * parentScene);
	~ShootingController();
	void timerActions();

};