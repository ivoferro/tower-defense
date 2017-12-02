#include "../../headers/gameobjects/ShootingController.h"
#include "../../headers/gameobjects/Bullet.h"
#include "../../headers/components/Transform.h"
#include "../../headers/framework/Application.h"
#include "../../headers/util/Math.h"

void ShootingController::spawnBullet()
{
	Transform * playerTransform = (Transform*)parentScene->
		gameObjects["player"]->getComponentById("transform");

	Bullet * bullet = new Bullet(parentScene);
	Transform * bulletTransform = (Transform*)bullet->getComponentById("transform");
	bulletTransform->rotation->y = playerTransform->rotation->z;
	bulletTransform->position->x = playerTransform->position->x + 1 * cos(Math::radians(playerTransform->rotation->z - 90));
	bulletTransform->position->y = playerTransform->position->y + 1 * sin(Math::radians(playerTransform->rotation->z - 90));
	bulletTransform->position->z = 2;
}

ShootingController::ShootingController(Scene * parentScene)
{
	this->parentScene = parentScene;
	this->player = (Player*)parentScene->gameObjects["player"];
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
		if (player->isAlive)
		{
			spawnBullet();
			isOnCooldown = true;
			timer = time(0);
		}
	}
}
