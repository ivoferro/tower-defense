#include "../../headers/gameobjects/Boss.h"
#include "../../headers/gameobjects/Bullet.h"
#include "../../headers/gameobjects/Tower.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/Collider.h"
#include "../../headers/components/TargetPath.h"
#include "../../headers/util/Math.h"

Boss::Boss()
{
	model = new MDLModel(2, 3, 3, 9, 16, 16, "resources/boss/zbs_bossl_big05.mdl");
	lifebar = new LifeBar(this, 5.0f, 90.0f);
	isAlive = GL_TRUE;

	addComponent("transform", new Transform());
	addComponent("transformLifeBar", new Transform());
	addComponent("targetPath", new TargetPath());
	addComponent("life", new Life(500.0f, 500.0f));

	setUpCollider();
}

Boss::~Boss()
{
}

void Boss::setUpCollider()
{
	Collider * collider = new Collider(this);
	collider->addBox(
		new Transform::Coordinates(5, 5, 3),
		new Transform::Coordinates(-5, -5, -3));

	collider->registerOnCollisionEnterCallback(&GameObject::onCollisionEnter);
	addComponent("collider", collider);
}

void Boss::onCollisionEnter(GameObject * collidingObject)
{
	if (model->state == Death) return;

	Life * life = (Life*)getComponentById("life");
	if (Bullet * bullet = dynamic_cast<Bullet*>(collidingObject))
	{
		life->health -= bullet->damage;
		if (life->health <= 0)
		{
			model->death(glutGet(GLUT_ELAPSED_TIME));
		}
	}

	if (Tower * tower = dynamic_cast<Tower*>(collidingObject))
	{
		model->attack(glutGet(GLUT_ELAPSED_TIME));
	}
}

void Boss::draw()
{
	lifebar->draw();

	model->init();

	Transform * t = (Transform*)getComponentById("transform");
	glPushMatrix();
		glTranslatef(-0.8f, -0.8f, -2.0f); // model pivot point

		glTranslatef(t->position->x, t->position->y, t->position->z);
		glRotatef(t->rotation->x, 1, 0, 0);
		glRotatef(t->rotation->y, 0, 1, 0);
		glRotatef(t->rotation->z, 0, 0, 1);
		glScalef(t->scale->x, t->scale->y, t->scale->z);

		glScalef(0.04, 0.04, 0.04);
		model->draw();

	glPopMatrix();
}

void Boss::timerActions()
{
	Transform * bossTransform = (Transform*)getComponentById("transform");

	// ***********************************************************
	// state control (eg. walking, sidewalking, attacking, etc..)
	if (model->state == Death)
	{
		if (!model->stillDying(glutGet(GLUT_ELAPSED_TIME), 11290))
		{
			isAlive = GL_FALSE;
			model->dead();
			bossTransform->position->z = -0.3;
		}
		return;
	}

	if (model->state == Attacking)
	{
		model->attack(glutGet(GLUT_ELAPSED_TIME));
	}
	if (model->stillShooting(glutGet(GLUT_ELAPSED_TIME), 4330))
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
	Transform::Coordinates * currentLocation = bossTransform->position;

	GLfloat speed = 0.2f;
	GLfloat elapsed = 0.01f;

	GLfloat distance = Math::distance2D(currentLocation, nextObjective);
	Transform::Coordinates * subtractedVecs = Math::subtract(nextObjective, currentLocation);
	Transform::Coordinates * direction = Math::normalize(subtractedVecs);

	currentLocation->x += direction->x * speed;
	currentLocation->y += direction->y * speed;


	bossTransform->rotation->z = atan2(
		nextObjective->y - currentLocation->y,
		nextObjective->x - currentLocation->x);
	bossTransform->rotation->z = (bossTransform->rotation->z * (180 / M_PI));


	if (distance <= 0.01)
	{
		targetPath->popCoordinate();
	}

	delete subtractedVecs;
	delete direction;
}

void Boss::animate()
{
	model->animate();
}
