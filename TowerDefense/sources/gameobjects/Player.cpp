#include "../../headers/gameobjects/Player.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/CharacterPhysics.h"

Player::Player()
{
	addComponent("transform", new Transform());
	addComponent("physics", new CharacterPhysics());
}

Player::~Player()
{
}

void Player::draw()
{
	Transform * t = (Transform*) getComponentById("transform");

	glPushMatrix();
	glTranslatef(t->position->x, t->position->y, t->position->z);
	glRotatef(t->rotation->z, 0, 0, 1);
	glScalef(1, 1, 2);
	drawCube();
	glPopMatrix();
}

void Player::drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat cor[])
{
	glBegin(GL_POLYGON);
	glColor3fv(cor);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();
}


void Player::drawCube()
{
	GLfloat vertices[][3] = { 
		{ -0.5, -0.5, -0.5 },
		{  0.5, -0.5, -0.5 },
		{  0.5,  0.5, -0.5 },
		{ -0.5,  0.5, -0.5 },
		{ -0.5, -0.5,  0.5 },
		{  0.5, -0.5,  0.5 },
		{  0.5,  0.5,  0.5 },
		{ -0.5,  0.5,  0.5 } };

	GLfloat colors[][3] = { 
		{ 0.5, 0.0, 0.0 },
		{ 0.0, 0.5, 0.0 },
		{ 0.0, 0.0, 0.5 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 0.0, 1.0 } };

	drawPolygon(vertices[1], vertices[0], vertices[3], vertices[2], colors[0]);
	drawPolygon(vertices[2], vertices[3], vertices[7], vertices[6], colors[1]);
	drawPolygon(vertices[3], vertices[0], vertices[4], vertices[7], colors[2]);
	drawPolygon(vertices[6], vertices[5], vertices[1], vertices[2], colors[3]);
	drawPolygon(vertices[4], vertices[5], vertices[6], vertices[7], colors[4]);
	drawPolygon(vertices[5], vertices[4], vertices[0], vertices[1], colors[5]);
}