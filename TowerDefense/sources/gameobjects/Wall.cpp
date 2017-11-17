#include "../../headers/gameobjects/Wall.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/Collider.h"
#include "../../headers/util/Illumination.h"

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
	glBegin(GL_POLYGON);

	GLfloat mat_ambient[] = { 0.5, 0.2, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.5, 0.2, 0.2, 1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Illumination::MATERIAL_SPECULAR);
	glMaterialfv(GL_FRONT, GL_SHININESS, Illumination::HIGH_SHININESS);
	glMaterialfv(GL_FRONT, GL_EMISSION, Illumination::MATERIAL_EMISSION);

	glNormal3fv(normal);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);

	glEnd();
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