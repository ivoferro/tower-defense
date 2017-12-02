#pragma once

#include "../framework/GameObject.h"
#include "../framework/Scene.h"
#include "../gameobjects/Player.h"
#include <time.h>

class ShootingController : public GameObject
{

private:
	Scene * parentScene;
	Player * player;
	time_t timer;
	GLfloat cooldownSeconds;
	GLboolean isOnCooldown;
	void spawnBullet();

public:
	ShootingController(Scene * parentScene);
	~ShootingController();
	void timerActions();

};