#include "../../headers/gameobjects/ShootingController.h"
#include "../../headers/gameobjects/Bullet.h"
#include "../../headers/components/Transform.h"
#include "../../headers/framework/Application.h"

void ShootingController::spawnBullet()
{
	Transform * playerTransform = (Transform*)parentScene->
		gameObjects["player"]->getComponentById("transform");

	Bullet * bullet = new Bullet(parentScene);
	Transform * bulletTransform = (Transform*)bullet->getComponentById("transform");
	bulletTransform->position->x = playerTransform->position->x;
	bulletTransform->position->y = playerTransform->position->y - 1;
	bulletTransform->position->z = 1;
}

ShootingController::ShootingController(Scene * parentScene)
{
	this->parentScene = parentScene;
	cooldownSeconds = 1;
	isOnCooldown = false;
}

ShootingController::~ShootingController()
{
}

void ShootingController::timerActions()
{

	if (isOnCooldown && ((double)difftime(time(0), timer) >= (double)cooldownSeconds))
	{
		isOnCooldown = false;
	}

	if (Application::instance()->getState()->getInputs()->playerShooting
		&& !isOnCooldown)
	{
		spawnBullet();
		isOnCooldown = true;
		timer = time(0);
	}
}
