#include "../../headers/gameobjects/Wall.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/Collider.h"
#include "../../headers/util/Illumination.h"
#include "../../headers/framework/Application.h"

Wall::Wall()
{
	addComponent("transform", new Transform());

	setUpCollider();
}

Wall::~Wall()
{
}

void Wall::draw()
{
	if (!Application::instance()->getTextures()->areTexturesLoaded)
	{
		return;
	}

	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();
		glTranslatef(t->position->x, t->position->y, t->position->z);
		glRotatef(t->rotation->x, 1, 0, 0);
		glRotatef(t->rotation->y, 0, 1, 0);
		glRotatef(t->rotation->z, 0, 0, 1);
		glScalef(t->scale->x, t->scale->y, t->scale->z);
		
		drawCube();
	glPopMatrix();
}

void Wall::drawCube()
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
		{  0,  1,  0 },
		{ -1,  0,  0 },
		{  0,  -1, 0 },
		{  1,  0,  0 },
		{  0,  0,  1 },
		{  0,  0, -1 } };

	drawPolygon(vertices[0], vertices[3], vertices[2], vertices[1], normals[0]);
	drawPolygon(vertices[1], vertices[2], vertices[6], vertices[5], normals[1]);
	drawPolygon(vertices[5], vertices[6], vertices[7], vertices[4], normals[2]);
	drawPolygon(vertices[4], vertices[7], vertices[3], vertices[0], normals[3]);
	drawPolygon(vertices[1], vertices[5], vertices[4], vertices[0], normals[4]);
	drawPolygon(vertices[2], vertices[3], vertices[7], vertices[6], normals[5]);
}

void Wall::drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat d[], GLfloat normal[])
{

	Transform * t = (Transform*)getComponentById("transform");

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, Application::instance()->getTextures()->getTexture("metal_plate"));

	glBegin(GL_QUADS);

	glNormal3fv(normal);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(a);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(b);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(c);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(d);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void Wall::setUpCollider()
{
	Collider * collider = new Collider(this);
	collider->registerOnCollisionEnterCallback(&GameObject::onCollisionEnter);
	addComponent("collider", collider);
}

void Wall::onCollisionEnter(GameObject * collidingObject)
{
}