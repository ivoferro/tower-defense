#include "../../headers/gameobjects/Player.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/Collider.h"
#include "../../headers/components/CharacterPhysics.h"
#include "../../headers/gameobjects/LifeBar.h"
#include "../../headers/framework/Application.h"
#include "../../headers/util/Math.h"

Player::Player()
{
	addComponent("transform", new Transform());
	addComponent("physics", new CharacterPhysics());

	setUpCollider();
}

Player::~Player()
{
}

void Player::draw()
{
	Transform * t = (Transform*) getComponentById("transform");

	GLfloat color1[3] = { 1.0f, 0.9f, 0.5f };
	GLfloat color2[3] = { 0.9f, 0.5f, 1.0f };

	glPushMatrix();
		glTranslatef(t->position->x, t->position->y, t->position->z);
		glRotatef(t->rotation->x, 1, 0, 0);
		glRotatef(t->rotation->y, 0, 1, 0);
		glRotatef(t->rotation->z, 0, 0, 1);
		glScalef(t->scale->x, t->scale->y, t->scale->z);

		glScalef(0.5, 0.5, 0.5);

		// torso
		glPushMatrix();
			glScalef(1, 1, 2);
			drawCube(color1);
		glPopMatrix();

		// head
		glPushMatrix();
			glTranslatef(0, 0, 1.5);
			glutSolidSphere(0.5, 16, 16);
		glPopMatrix();

		// left arm
		glPushMatrix();
			glTranslatef(0.3, 0, -2);
			glScalef(0.4, 0.4, 2);
			drawCube(color2);
		glPopMatrix();

		// right arm
		glPushMatrix();
			glTranslatef(-0.3, 0, -2);
			glScalef(0.4, 0.4, 2);
			drawCube(color2);
		glPopMatrix();

		// left leg
		glPushMatrix();
			glTranslatef(1, 0, 0);
			glRotatef(-20, 0, 1, 0);
			glScalef(0.4, 0.4, 2);
			drawCube(color2);
		glPopMatrix();

		// right leg
		glPushMatrix();
			glTranslatef(-1, 0, 0);
			glRotatef(20, 0, 1, 0);
			glScalef(0.4, 0.4, 2);
			drawCube(color2);
		glPopMatrix();

	glPopMatrix();

	// ****** LIFEBAR ******
	LifeBar *lifebar = new LifeBar();
	Transform * lt = (Transform*)lifebar->getComponentById("transformLifeBar");
	//Transform * e1t_lifebar = (Transform*)e1->getComponentById("transformLifeBar");
	lt->position->x = t->position->x;
	lt->position->y = t->position->y;
	lt->position->z = (t->position->z + 1.2); // ... + val -> above the object

	// change scale->x between 0 and 1 scale->x when lifebar need to be reduced
	lt->scale->x = 0.5;
	lt->scale->y = 0.1;
	lt->scale->z = 0.1;

	lt->rotation->z = t->rotation->z;

	glPushMatrix();
	lifebar->draw();
	glPopMatrix();
}

void Player::drawCube(GLfloat color[])
{
	GLfloat vertices[][3] = {
		{ 0.5,  0.5,  0.5 },
		{ -0.5,  0.5,  0.5 },
		{ -0.5,  0.5, -0.5 },
		{ 0.5,  0.5, -0.5 },
		{ 0.5, -0.5,  0.5 },
		{ -0.5, -0.5,  0.5 },
		{ -0.5, -0.5, -0.5 },
		{ 0.5, -0.5, -0.5 } };

	GLfloat normals[][3] = {
		{ 0,  1,  0 },
		{ -1,  0,  0 },
		{ 0,  -1, 0 },
		{ 1,  0,  0 },
		{ 0,  0,  1 },
		{ 0,  0, -1 } };

	drawPolygon(vertices[0], vertices[3], vertices[2], vertices[1], normals[0], color);
	drawPolygon(vertices[1], vertices[2], vertices[6], vertices[5], normals[1], color);
	drawPolygon(vertices[5], vertices[6], vertices[7], vertices[4], normals[2], color);
	drawPolygon(vertices[4], vertices[7], vertices[3], vertices[0], normals[3], color);
	drawPolygon(vertices[1], vertices[5], vertices[4], vertices[0], normals[4], color);
	drawPolygon(vertices[2], vertices[3], vertices[7], vertices[6], normals[5], color);
}

void Player::drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat normal[], GLfloat color[])
{
	glBegin(GL_POLYGON);

	/*GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };*/

	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	/*glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);*/

	glColor3fv(color);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();
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

void Player::timerActions()
{
	Transform * playerT = (Transform*) getComponentById("transform");
	CharacterPhysics * playerPhy = (CharacterPhysics*) getComponentById("physics");

	// acelarations
	if (Application::instance()->getState()->getInputs()->move_player_front)
	{
		if (playerPhy->velocity < playerPhy->maxFrontVelocity)
		{
			playerPhy->velocity += 0.01;
		}
	}
	if (Application::instance()->getState()->getInputs()->move_player_back)
	{
		if (playerPhy->velocity > -playerPhy->maxBackVelocity)
		{
			playerPhy->velocity -= 0.01;
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
		}
	}
	if (Application::instance()->getState()->getInputs()->move_player_right)
	{
		if (playerPhy->sideVelocity > -playerPhy->maxSideVelocity)
		{
			playerPhy->sideVelocity -= 0.01;
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
