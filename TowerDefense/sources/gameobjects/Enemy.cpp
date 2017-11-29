#include "../../headers/gameobjects/Enemy.h"
#include "../../headers/gameobjects/LifeBar.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/Collider.h"
#include "../../headers/components/TargetPath.h"
#include "../../headers/util/Illumination.h"
#include "../../headers/mdlloader/Mdlloader.h"
#include "../../headers/mdlloader/studio.h"
#include "../../headers/util/Math.h"

typedef struct MODEL {
	GLboolean	isInit;
	StudioModel   mdl;   // MDL Model
	GLboolean     walking;
	GLuint        prev;
}MODEL;

MODEL model;

Enemy::Enemy()
{
	//mdlviewer_init("resources/enemy/zombie.mdl", model.mdl);

	addComponent("transform", new Transform());
	addComponent("transformLifeBar", new Transform());
	addComponent("targetPath", new TargetPath());

	setUpCollider();
}


Enemy::~Enemy()
{
}

void Enemy::drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat normal[], GLfloat color[])
{
	glBegin(GL_POLYGON);

	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Illumination::NO_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SHININESS, Illumination::NO_SHININESS);
	glMaterialfv(GL_FRONT, GL_EMISSION, Illumination::NO_MATERIAL);

	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();
}

void Enemy::setUpCollider()
{
	Collider * collider = new Collider(this);
	collider->addBox(
		new Transform::Coordinates(0.5, 0.5, 1),
		new Transform::Coordinates(-0.5, -0.5, -1));

	collider->registerOnCollisionEnterCallback(&GameObject::onCollisionEnter);
	addComponent("collider", collider);
}

void Enemy::onCollisionEnter(GameObject * collidingObject)
{
}

void Enemy::initEnemy()
{
	if (model.isInit == GL_FALSE)
	{
		mdlviewer_init("resources/enemy/zombie.mdl", model.mdl);
		model.isInit = GL_TRUE;
	}
}

void Enemy::draw()
{
	initEnemy();
	// ****** ENEMY ******
	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();
	glTranslatef(t->position->x, t->position->y, t->position->z);
	glTranslatef(0, 0, 1);
	glRotatef(90.0, 0,0,1);
	glScalef(0.035, 0.035, 0.035);
	mdlviewer_display(model.mdl);
	glPopMatrix();

	// ****** LIFEBAR ******
	LifeBar *lifebar = new LifeBar();
	Transform * lt = (Transform*)lifebar->getComponentById("transformLifeBar");
	//Transform * e1t_lifebar = (Transform*)e1->getComponentById("transformLifeBar");
	lt->position->x = t->position->x;
	lt->position->y = t->position->y;
	lt->position->z = (t->position->z + 2.5); // ... + val -> above the object

	// change scale->x between 0 and 1 scale->x when lifebar need to be reduced
	lt->scale->x = 0.85;
	lt->scale->y = 0.1;
	lt->scale->z = 0.1;

	glPushMatrix();
	lifebar->draw();
	glPopMatrix();	
}

void Enemy::timerActions()
{

	// if sensoring targets atack them

	TargetPath * targetPath = (TargetPath*)getComponentById("targetPath");
	if (targetPath->isObjectivesEmpty())
	{
		return;
	}

	Transform::Coordinates * nextObjective = targetPath->nextObjective();
	Transform::Coordinates * currentLocation = ((Transform*)getComponentById("transform"))->position;

	GLfloat speed = 0.2f;
	GLfloat elapsed = 0.01f;

	GLfloat distance = Math::distance2D(currentLocation, nextObjective);
	Transform::Coordinates * subtractedVecs = Math::subtract(nextObjective, currentLocation);
	Transform::Coordinates * direction = Math::normalize(subtractedVecs);

	currentLocation->x += direction->x * speed;
	currentLocation->y += direction->y * speed;
	if (distance <= 0.01)
	{
		targetPath->popCoordinate();
	}

	delete subtractedVecs;
	delete direction;

	if (model.isInit)
	{
		model.mdl.SetSequence(3);
	}
}
