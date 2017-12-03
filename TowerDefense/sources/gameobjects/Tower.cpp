#include "../../headers/gameobjects/Tower.h"
#include "../../headers/gameobjects/Enemy.h"
#include "../../headers/gameobjects/Boss.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/Collider.h"
#include "../../headers/components/Life.h"
#include "../../headers/objloader/glm.h"

GLMmodel* towerModel = NULL;

Tower::Tower()
{
	lifebar = new LifeBar(this, 3.5f, 0.0f);

	addComponent("transform", new Transform());
	addComponent("life", new Life(500.0f, 500.0f));
	setUpCollider();

	gameover = GL_FALSE;
	prevAttack = glutGet(GLUT_ELAPSED_TIME);
}

Tower::~Tower()
{
}

void Tower::initModel()
{
	// Load the model only if it hasn't been loaded before
	// If it's been loaded then pmodel1 should be a pointer to the model geometry data...otherwise it's null
	if (!towerModel)
	{
		// this is the call that actualy reads the OBJ and creates the model object
		towerModel = glmReadOBJ("resources/tower/Tower_obj.obj", "resources/tower/Texture_.tga");
		if (!towerModel) exit(0);
		// This will rescale the object to fit into the unity matrix
		// Depending on your project you might want to keep the original size and positions you had in 3DS Max or GMAX so you may have to comment this.
		glmUnitize(towerModel);
		// These 2 functions calculate triangle and vertex normals from the geometry data.
		// To be honest I had some problem with very complex models that didn't look to good because of how vertex normals were calculated
		// So if you can export these directly from you modeling tool do it and comment these line
		// 3DS Max can calculate these for you and GLM is perfectly capable of loading them
		glmFacetNormals(towerModel);
		glmVertexNormals(towerModel, 90.0);
	}

	// This is the call that will actualy draw the model
	// Don't forget to tell it if you want textures or not :))
	glmDraw(towerModel, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
}

void Tower::draw()
{
	Transform * t = (Transform*)getComponentById("transform");

	lifebar->draw();

	glPushMatrix();
		glTranslatef(t->position->x, t->position->y, t->position->z);
		glRotatef(t->rotation->x, 1, 0, 0);
		glRotatef(t->rotation->y, 0, 1, 0);
		glRotatef(t->rotation->z, 0, 0, 1);
		glScalef(t->scale->x, t->scale->y, t->scale->z);

		glScalef(3, 3, 3);
		initModel();
	glPopMatrix();

}

void Tower::setUpCollider()
{
	Collider * collider = new Collider(this);
	collider->addBox(
		new Transform::Coordinates(2.25, 2.25, 3),
		new Transform::Coordinates(-0.75, -0.75, -3));

	collider->registerOnCollisionEnterCallback(&GameObject::onCollisionEnter);
	addComponent("collider", collider);
}

void Tower::onCollisionEnter(GameObject * collidingObject)
{
	Life * life = (Life*)getComponentById("life");
	if (Enemy * enemy = dynamic_cast<Enemy*>(collidingObject))
	{
		if (enemy->model->state == Attacking && (glutGet(GLUT_ELAPSED_TIME) - prevAttack) > 1000)
		{
			prevAttack = glutGet(GLUT_ELAPSED_TIME);
			life->health -= 20;
			if (life->health <= 0)
			{
				gameover = GL_TRUE;
			}
		}
	}
	if (Boss * boss = dynamic_cast<Boss*>(collidingObject))
	{
		if (boss->model->state == Attacking && (glutGet(GLUT_ELAPSED_TIME) - prevAttack) > 4300)
		{
			prevAttack = glutGet(GLUT_ELAPSED_TIME);
			life->health -= 50;
			if (life->health <= 0)
			{
				gameover = GL_TRUE;
			}
		}
	}
}

