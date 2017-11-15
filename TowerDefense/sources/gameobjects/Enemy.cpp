#include "../../headers/gameobjects/Enemy.h"
#include "../../headers/components/Transform.h"
#include "../../headers/gameobjects/LifeBar.h"

Enemy::Enemy()
{
	addComponent("transform", new Transform());
	addComponent("transformLifeBar", new Transform());

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
	GLfloat vertices[][3] = {
		{ 0.5,  0.5,  0.5 },
		{ -0.5,  0.5,  0.5 },
		{ -0.5,  0.5, -0.5 },
		{ 0.5,  0.5, -0.5 },
		{ 0.5, -0.5,  0.5 },
		{ -0.5, -0.5,  0.5 },
		{ -0.5, -0.5, -0.5 },
		{ 0.5, -0.5, -0.5 } };

	GLfloat colors[][3] = {
		{ 0.5, 0.0, 0.0 },
		{ 0.0, 0.5, 0.0 },
		{ 0.0, 0.0, 0.5 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 0.0, 1.0 } };

	drawPolygon(vertices[0], vertices[3], vertices[2], vertices[1], colors[0]);
	drawPolygon(vertices[1], vertices[2], vertices[6], vertices[5], colors[1]);
	drawPolygon(vertices[5], vertices[6], vertices[7], vertices[4], colors[2]);
	drawPolygon(vertices[4], vertices[7], vertices[3], vertices[0], colors[3]);
	drawPolygon(vertices[1], vertices[5], vertices[4], vertices[0], colors[4]);
	drawPolygon(vertices[2], vertices[3], vertices[7], vertices[6], colors[5]);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Enemy::draw()
{
	
	

	// ****** ENEMY ******
	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();
	glTranslatef(t->position->x, t->position->y, t->position->z);
	glScalef(1, 1, 2);
	drawEnemy();
	glPopMatrix();

	// ****** LIFEBAR ******
	LifeBar *lifebar = new LifeBar();
	Transform * lt = (Transform*)lifebar->getComponentById("transformLifeBar");
	//Transform * e1t_lifebar = (Transform*)e1->getComponentById("transformLifeBar");
	lt->position->x = t->position->x;
	lt->position->y = t->position->y;
	lt->position->z = (t->position->z + 1.2); // ... + val -> above the object

	// change between 0 and 1 scale->x when lifebar need to be reduced
	lt->scale->x = t->scale->x + 0.5;
	lt->scale->y = t->scale->y + 0.1;
	lt->scale->z = t->scale->z + 0.1;

	glPushMatrix();
	lifebar->draw();
	glPopMatrix();

	
}

