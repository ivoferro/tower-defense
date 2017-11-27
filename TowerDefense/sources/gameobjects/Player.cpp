#include "../../headers/gameobjects/Player.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/Collider.h"
#include "../../headers/components/CharacterPhysics.h"
#include "../../headers/gameobjects/LifeBar.h"
#include "../../headers/framework/Application.h"
#include "../../headers/util/Math.h"
#include "../../headers/util/Illumination.h"
#include "../../headers/objloader/glm.h"

GLMmodel* model1 = NULL;

Player::Player()
{
	addComponent("transform", new Transform());
	addComponent("physics", new CharacterPhysics());

	setUpCollider();
}

Player::~Player()
{
}

void Player::initModel()
{
	// Load the model only if it hasn't been loaded before
	// If it's been loaded then pmodel1 should be a pointer to the model geometry data...otherwise it's null
	if (!model1)
	{
		// this is the call that actualy reads the OBJ and creates the model object
		model1 = glmReadOBJ("resources/player/FLASH.obj", NULL);
		if (!model1) exit(0);
		// This will rescale the object to fit into the unity matrix
		// Depending on your project you might want to keep the original size and positions you had in 3DS Max or GMAX so you may have to comment this.
		glmUnitize(model1);
		// These 2 functions calculate triangle and vertex normals from the geometry data.
		// To be honest I had some problem with very complex models that didn't look to good because of how vertex normals were calculated
		// So if you can export these directly from you modeling tool do it and comment these line
		// 3DS Max can calculate these for you and GLM is perfectly capable of loading them
		glmFacetNormals(model1);
		glmVertexNormals(model1, 90.0);
	}

	// This is the call that will actualy draw the model
	// Don't forget to tell it if you want textures or not :))
	//idleFrames.push_back(glmList(model, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL));
	//dl = glmList(model, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
	glmDraw(model1, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
}


void Player::draw()
{
	Transform * t = (Transform*) getComponentById("transform");

	GLfloat color1[3] = { 0.15f, 0.15f, 0.45f };
	GLfloat color2[3] = { 0.05f, 0.15f, 0.25f };

	GLfloat headColor[3] = { 0.75f, 0.5f, 0.25f };

	glPushMatrix();
		glTranslatef(t->position->x, t->position->y, t->position->z);
		glRotatef(t->rotation->x, 1, 0, 0);
		glRotatef(t->rotation->y, 0, 1, 0);
		glRotatef(t->rotation->z, 0, 0, 1);
		glScalef(t->scale->x, t->scale->y, t->scale->z);

		glTranslatef(0, 0, 0);
		glRotatef(90.0, 1, 0, 0);
		glScalef(1.3, 1.3, 1.3);
		initModel();
	glPopMatrix();

	// ****** LIFEBAR ******
	LifeBar *lifebar = new LifeBar();
	Transform * lt = (Transform*)lifebar->getComponentById("transformLifeBar");
	//Transform * e1t_lifebar = (Transform*)e1->getComponentById("transformLifeBar");
	lt->position->x = t->position->x;
	lt->position->y = t->position->y;
	lt->position->z = (t->position->z + 1.8); // ... + val -> above the object

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

	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Illumination::NO_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SHININESS, Illumination::NO_SHININESS);
	glMaterialfv(GL_FRONT, GL_EMISSION, Illumination::NO_MATERIAL);

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
