#include "../../headers/gameobjects/Enemy.h"
#include "../../headers/gameobjects/Bullet.h"
#include "../../headers/gameobjects/Tower.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/Collider.h"
#include "../../headers/components/TargetPath.h"
#include "../../headers/components/Life.h"
#include "../../headers/util/Illumination.h"
#include "../../headers/mdlloader/Mdlloader.h"
#include "../../headers/mdlloader/studio.h"
#include "../../headers/util/Math.h"

Enemy::Enemy()
{
	model = new MDLModel(0,4,4,26,19,73, "resources/enemy/zombie.mdl");
	lifebar = new LifeBar(this, 3.0f, 90.0f);

	addComponent("transform", new Transform());
	addComponent("targetPath", new TargetPath());
	addComponent("life", new Life(100.0f, 100.0f));

	setUpCollider();
}

Enemy::~Enemy()
{
}

void Enemy::setUpCollider()
{
	Collider * collider = new Collider(this);
	collider->addBox(
		new Transform::Coordinates(1, 1, 1),
		new Transform::Coordinates(-1, -1, -1));

	collider->registerOnCollisionEnterCallback(&GameObject::onCollisionEnter);
	addComponent("collider", collider);
}

void Enemy::onCollisionEnter(GameObject * collidingObject)
{
	if (model->state == Death) return;

	Life * life = (Life*)getComponentById("life");
	if (Bullet * bullet = dynamic_cast<Bullet*>(collidingObject))
	{
		life->health -= bullet->damage;
		if (life->health <= 0)
		{
			isAlive = false;
			model->death(glutGet(GLUT_ELAPSED_TIME));
		}
	}

	if (Tower * tower = dynamic_cast<Tower*>(collidingObject))
	{
		model->attack(glutGet(GLUT_ELAPSED_TIME));
	}
}

void Enemy::initModel()
{
	model->init();
}

void Enemy::drawModel()
{
	model->draw();
}

void Enemy::draw()
{
	// Intitialize enemy MDL Model
	initModel();

	// ****** ENEMY ******
	Transform * t = (Transform*)getComponentById("transform");

	lifebar->draw();

	glPushMatrix();
		glTranslatef(t->position->x, t->position->y, t->position->z);
		glRotatef(t->rotation->x, 1, 0, 0);
		glRotatef(t->rotation->y, 0, 1, 0);
		glRotatef(t->rotation->z, 0, 0, 1);
		glScalef(t->scale->x, t->scale->y, t->scale->z);

		glScalef(0.05, 0.05, 0.05);

		drawModel();
	glPopMatrix();
}

void Enemy::timerActions()
{
	Transform * enemyT = (Transform*)getComponentById("transform");

	// ***********************************************************
	// state control (eg. walking, sidewalking, attacking, etc..)
	if (model->state == Death)
	{
		if (!model->stillDying(glutGet(GLUT_ELAPSED_TIME), 900))
		{
			model->dead();
			enemyT->position->z = 0;
		}
		return;
	}

	if (model->state == Attacking)
	{
		model->attack(glutGet(GLUT_ELAPSED_TIME));
	}
	if (model->stillShooting(glutGet(GLUT_ELAPSED_TIME), 500))
	{
		return;
	}

	TargetPath * targetPath = (TargetPath*)getComponentById("targetPath");
	// if sensoring targets atack them
	if (targetPath->isObjectivesEmpty())
	{
		model->idle();
		return;
	}
	else
	{
		model->walk();
	}

	Transform::Coordinates * nextObjective = targetPath->nextObjective();

	Transform * currentT = ((Transform*)getComponentById("transform"));
	Transform::Coordinates * currentLocation = currentT->position;

	GLfloat speed = 0.1f;
	GLfloat elapsed = 0.01f;

	GLfloat distance = Math::distance2D(currentLocation, nextObjective);
	Transform::Coordinates * subtractedVecs = Math::subtract(nextObjective, currentLocation);
	Transform::Coordinates * direction = Math::normalize(subtractedVecs);

	currentLocation->x += direction->x * speed;
	currentLocation->y += direction->y * speed;


	currentT->rotation->z = atan2(
		nextObjective->y - currentLocation->y,
		nextObjective->x - currentLocation->x);
	currentT->rotation->z = (currentT->rotation->z * (180 / M_PI));


	if (distance <= 0.01)
	{
		targetPath->popCoordinate();
	}

	delete subtractedVecs;
	delete direction;
}

void Enemy::animate()
{
	model->animate();
}