#include "../../headers/gameobjects/Bullet.h"
#include "../../headers/gameobjects/Player.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/Collider.h"
#include "../../headers/objloader/glm.h"
#include "../../headers/util/Math.h"

void Bullet::setUpCollider()
{
	Collider * collider = new Collider(this);
	collider->addBox(
		new Transform::Coordinates(0.1f, 0.1f, 0.1f),
		new Transform::Coordinates(-0.1f, -0.1f, -0.1f));

	collider->registerOnCollisionEnterCallback(&GameObject::onCollisionEnter);
	addComponent("collider", collider);
}

void Bullet::onCollisionEnter(GameObject * collidingObject)
{
	// TODO expload!!!
	if (Player * player = dynamic_cast<Player*>(collidingObject))
	{
		return;
	}
	doRemove = true;
}

void Bullet::initModel()
{
	// Load the model only if it hasn't been loaded before
	// If it's been loaded then pmodel1 should be a pointer to the model geometry data...otherwise it's null
	if (!bulletModel)
	{
		// this is the call that actualy reads the OBJ and creates the model object
		bulletModel = glmReadOBJ("resources/bullet/bullet.obj", "resources/bullet/bullet.tga");
		if (!bulletModel) exit(0);
		// This will rescale the object to fit into the unity matrix
		// Depending on your project you might want to keep the original size and positions you had in 3DS Max or GMAX so you may have to comment this.
		glmUnitize(bulletModel);
		// These 2 functions calculate triangle and vertex normals from the geometry data.
		// To be honest I had some problem with very complex models that didn't look to good because of how vertex normals were calculated
		// So if you can export these directly from you modeling tool do it and comment these line
		// 3DS Max can calculate these for you and GLM is perfectly capable of loading them
		glmFacetNormals(bulletModel);
		glmVertexNormals(bulletModel, 90.0);
	}

	// This is the call that will actualy draw the model
	// Don't forget to tell it if you want textures or not :))
	glmDraw(bulletModel, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
}

Bullet::Bullet(Scene * parentScene)
{
	this->parentScene = parentScene;

	Transform * t = new Transform();
	t->scale->x = .3;
	t->scale->y = .3;
	t->scale->z = .3;
	t->rotation->x = 90;
	addComponent("transform", t);
	setUpCollider();

	id = this->parentScene->addToWaitingObjects(this);
	this->parentScene->activateObject(id);
}

Bullet::~Bullet()
{
}

void Bullet::draw()
{
	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();
		glTranslatef(t->position->x, t->position->y, t->position->z);
		glRotatef(t->rotation->x, 1, 0, 0);
		glRotatef(t->rotation->y, 0, 1, 0);
		glRotatef(t->rotation->z, 0, 0, 1);
		glScalef(t->scale->x, t->scale->y, t->scale->z);
		initModel();
	glPopMatrix();
}

void Bullet::timerActions()
{
	Transform * t = (Transform*)getComponentById("transform");

	GLfloat speed = 1.0f;
	t->position->x += speed * cos(Math::radians(t->rotation->y - 90));
	t->position->y += speed * sin(Math::radians(t->rotation->y - 90));
}
