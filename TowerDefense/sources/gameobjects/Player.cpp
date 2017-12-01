#include "../../headers/gameobjects/Player.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/Collider.h"
#include "../../headers/components/CharacterPhysics.h"
#include "../../headers/gameobjects/LifeBar.h"
#include "../../headers/framework/Application.h"
#include "../../headers/util/Math.h"
#include "../../headers/util/Illumination.h"

Player::Player()
{
	model = new MDLModel();
	timer = 0;

	addComponent("transform", new Transform());
	addComponent("physics", new CharacterPhysics());

	setUpCollider();
}

Player::~Player()
{
}

void Player::initModel()
{
	if (model->isInit == GL_FALSE)
	{
		mdlviewer_init("resources/player/player.mdl", model->model);
		model->isInit = GL_TRUE;
	}
}

void Player::drawModel()
{
	mdlviewer_display(model->model);
}


void Player::draw()
{
	// Intitialize enemy MDL Model
	initModel();

	Transform * t = (Transform*) getComponentById("transform");

	glPushMatrix();
		glTranslatef(t->position->x, t->position->y, t->position->z);
		glRotatef(t->rotation->x, 1, 0, 0);
		glRotatef(t->rotation->y, 0, 1, 0);
		glRotatef(t->rotation->z, 0, 0, 1);
		glScalef(t->scale->x, t->scale->y, t->scale->z);

		// Initial values
		glTranslatef(0, 0, 0.3);
		glRotatef(-90.0, 0, 0, 1);
		glScalef(0.05, 0.05, 0.05);
		drawModel();
	glPopMatrix();

	// ****** LIFEBAR ******
	LifeBar *lifebar = new LifeBar();
	Transform * lt = (Transform*)lifebar->getComponentById("transformLifeBar");
	//Transform * e1t_lifebar = (Transform*)e1->getComponentById("transformLifeBar");
	lt->position->x = t->position->x;
	lt->position->y = t->position->y;
	lt->position->z = (t->position->z + 2.3); // ... + val -> above the object

	// change scale->x between 0 and 1 scale->x when lifebar need to be reduced
	lt->scale->x = 0.5;
	lt->scale->y = 0.1;
	lt->scale->z = 0.1;

	lt->rotation->z = t->rotation->z;

	glPushMatrix();
	lifebar->draw();
	glPopMatrix();
}

void Player::setUpCollider()
{
	Collider * collider = new Collider(this);
	collider->addBox(
		new Transform::Coordinates(0.75, 0.75, 1.25), 
		new Transform::Coordinates(-0.75, -0.75, -1.25));

	collider->registerOnCollisionEnterCallback(&GameObject::onCollisionEnter);
	addComponent("collider", collider);
}

void Player::onCollisionEnter(GameObject * collidingObject)
{
	isColliding = true;
}

void Player::timerActions(int value)
{
	//model->isWalking = GL_FALSE;

	Transform * playerT = (Transform*) getComponentById("transform");
	CharacterPhysics * playerPhy = (CharacterPhysics*) getComponentById("physics");

	// state control (eg. walking, sidewalking, attacking, etc..)
	if (playerPhy->velocity != 0)
	{
		model->walk();
	}
	else if (playerPhy->sideVelocity != 0)  {
		model->sideWalk();
	}
	else
	{
		model->idle();
	}

	GLuint curr = glutGet(GLUT_ELAPSED_TIME);
	model->prevSequence = curr;

	// acelarations
	if (Application::instance()->getState()->getInputs()->move_player_front)
	{
		if (playerPhy->velocity < playerPhy->maxFrontVelocity)
		{
			playerPhy->velocity += 0.01;
			//model->isWalking = GL_TRUE;
		}
	}
	if (Application::instance()->getState()->getInputs()->move_player_back)
	{
		if (playerPhy->velocity > -playerPhy->maxBackVelocity)
		{
			playerPhy->velocity -= 0.01;
			//model->isWalking = GL_TRUE;
		}
	}
	if (!Application::instance()->getState()->getInputs()->move_player_front &&
		!Application::instance()->getState()->getInputs()->move_player_back)
	{
		playerPhy->velocity = 0;
	}

	// side movements
	if (Application::instance()->getState()->getInputs()->move_player_left)
	{
		if (playerPhy->sideVelocity < playerPhy->maxSideVelocity)
		{
			playerPhy->sideVelocity += 0.01;
			//model->isWalking = GL_TRUE;
		}
	}
	if (Application::instance()->getState()->getInputs()->move_player_right)
	{
		if (playerPhy->sideVelocity > -playerPhy->maxSideVelocity)
		{
			playerPhy->sideVelocity -= 0.01;
			//model->isWalking = GL_TRUE;
		}
	}
	if (!Application::instance()->getState()->getInputs()->move_player_left &&
		!Application::instance()->getState()->getInputs()->move_player_right)
	{
		playerPhy->sideVelocity = 0;
	}

	oldTransform.position->x = playerT->position->x;
	oldTransform.position->y = playerT->position->y;
	oldTransform.position->z = playerT->position->z;

	// changes player position according to front/back movements
	playerT->position->x += playerPhy->velocity * cos(Math::radians(playerT->rotation->z - 90));
	playerT->position->y += playerPhy->velocity * sin(Math::radians(playerT->rotation->z - 90));
	// changes player position according to side movements
	playerT->position->x += playerPhy->sideVelocity * cos(Math::radians(playerT->rotation->z));
	playerT->position->y += playerPhy->sideVelocity * sin(Math::radians(playerT->rotation->z));
}

void Player::animate()
{
	if (model->isInit)
	{
		if (model->state == Walking)
		{
			if (model->model.GetSequence() != 3)
			{
				model->model.SetSequence(3);
			}
		}
		else if (model->state == SideWalking)
		{
			if (model->model.GetSequence() != 4)
			{
				model->model.SetSequence(4);
			}
		}
		else {
			model->model.SetSequence(0);
		}
	}
}

void Player::move()
{
	if (isColliding)
	{
		Transform * playerT = (Transform*)getComponentById("transform");
		playerT->position->x = oldTransform.position->x;
		playerT->position->y = oldTransform.position->y;
		playerT->position->z = oldTransform.position->z;
	}
}
