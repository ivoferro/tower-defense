#include "../../headers/gameobjects/Enemy.h"
#include "../../headers/components/Transform.h"

Enemy::Enemy()
{
	addComponent("transform", new Transform());
}


Enemy::~Enemy()
{
}

void Enemy::drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat cor[])
{
	/* draw a polygon via list of vertices */

	glBegin(GL_POLYGON);
	glColor3fv(cor);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();
}

void Enemy::drawEnemy()
{
	GLfloat vertices[][3] = { { -0.5,-0.5,-0.5 },
	{ 0.5,-0.5,-0.5 },
	{ 0.5,0.5,-0.5 },
	{ -0.5,0.5,-0.5 },
		// 2� face
	{ -0.5,-0.5, 0.5 },
	{ 0.5,-0.5, 0.5 },
	{ 0.5,0.5, 0.5 },
	{ -0.5,0.5, 0.5 } };

	GLfloat cores[][3] = { { 0.0,1.0,1.0 },
	{ 1.0,0.0,0.0 },
	{ 1.0,1.0,0.0 },
	{ 0.0,1.0,0.0 },
	{ 1.0,0.0,1.0 },
	{ 0.0,0.0,1.0 },
	{ 1.0,1.0,1.0 } };

	drawPolygon(vertices[1], vertices[0], vertices[3], vertices[2], cores[5]);
	drawPolygon(vertices[5], vertices[6], vertices[7], vertices[4], cores[4]);
	drawPolygon(vertices[1], vertices[2], vertices[6], vertices[5], cores[3]);
	drawPolygon(vertices[0], vertices[4], vertices[7], vertices[3], cores[2]);
	drawPolygon(vertices[2], vertices[3], vertices[7], vertices[6], cores[1]);
	drawPolygon(vertices[5], vertices[4], vertices[0], vertices[1], cores[0]);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Enemy::draw()
{
	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();
	glTranslatef(t->position->x, t->position->y, t->position->z);
	glScalef(3, 2, 1);
	drawEnemy();
	glPopMatrix();
}
