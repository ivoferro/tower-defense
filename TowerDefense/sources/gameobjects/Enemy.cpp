#include "../../headers/gameobjects/Enemy.h"
#include "../../headers/components/Transform.h"
#include "../../headers/gameobjects/LifeBar.h"
#include "../../headers/components/Collider.h"
#include "../../headers/util/Illumination.h"
#include "../../headers/objloader/glm.h"

GLMmodel* model = NULL;

Enemy::Enemy()
{
	//initModel();
	addComponent("transform", new Transform());
	addComponent("transformLifeBar", new Transform());

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

void Enemy::initModel()
{
	// Load the model only if it hasn't been loaded before
	// If it's been loaded then pmodel1 should be a pointer to the model geometry data...otherwise it's null
	if (!model)
	{
		// this is the call that actualy reads the OBJ and creates the model object
		model = glmReadOBJ("resources/enemy/idle/StrongZombie_000001.obj", "resources/enemy/StrongZombie.tga");
		if (!model) exit(0);
		// This will rescale the object to fit into the unity matrix
		// Depending on your project you might want to keep the original size and positions you had in 3DS Max or GMAX so you may have to comment this.
		glmUnitize(model);
		// These 2 functions calculate triangle and vertex normals from the geometry data.
		// To be honest I had some problem with very complex models that didn't look to good because of how vertex normals were calculated
		// So if you can export these directly from you modeling tool do it and comment these line
		// 3DS Max can calculate these for you and GLM is perfectly capable of loading them
		glmFacetNormals(model);
		glmVertexNormals(model, 90.0);
	}

	// This is the call that will actualy draw the model
	// Don't forget to tell it if you want textures or not :))
	//idleFrames.push_back(glmList(model, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL));
	//dl = glmList(model, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
	glmDraw(model, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
}

void Enemy::drawEnemy()
{

	//glCallList(dl);
	initModel();
}

void Enemy::draw()
{
	// ****** ENEMY ******
	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();
	glTranslatef(t->position->x, t->position->y, t->position->z);
	glTranslatef(0, 0, 1);
	glRotatef(90.0, 1, 0, 0);
	drawEnemy();
	glPopMatrix();

	// ****** LIFEBAR ******
	LifeBar *lifebar = new LifeBar();
	Transform * lt = (Transform*)lifebar->getComponentById("transformLifeBar");
	//Transform * e1t_lifebar = (Transform*)e1->getComponentById("transformLifeBar");
	lt->position->x = t->position->x;
	lt->position->y = t->position->y;
	lt->position->z = (t->position->z + 2.2); // ... + val -> above the object

	// change scale->x between 0 and 1 scale->x when lifebar need to be reduced
	lt->scale->x = 0.85;
	lt->scale->y = 0.1;
	lt->scale->z = 0.1;

	glPushMatrix();
	lifebar->draw();
	glPopMatrix();	
}