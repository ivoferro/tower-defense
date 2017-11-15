#include "../../headers/gameobjects/Player.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/Collider.h"
#include "../../headers/components/CharacterPhysics.h"
#include "../../headers/gameobjects/LifeBar.h"

Player::Player()
{
	addComponent("transform", new Transform());
	addComponent("physics", new CharacterPhysics());

	setUpCollider();
}

Player::~Player()
{
}

void Player::draw()
{
	Transform * t = (Transform*) getComponentById("transform");

	glPushMatrix();
		glTranslatef(t->position->x, t->position->y, t->position->z);
		glRotatef(t->rotation->x, 1, 0, 0);
		glRotatef(t->rotation->y, 0, 1, 0);
		glRotatef(t->rotation->z, 0, 0, 1);
		glScalef(t->scale->x, t->scale->y, t->scale->z);

		glScalef(0.5, 0.5, 0.5);

		// torso
		glPushMatrix();
			glScalef(1, 1, 2);
			drawCube();
		glPopMatrix();

		// head
		glPushMatrix();
			glTranslatef(0, 0, 1.5);
			glutSolidSphere(0.5, 16, 16);
		glPopMatrix();

		// left arm
		glPushMatrix();
			glTranslatef(0.3, 0, -2);
			glScalef(0.4, 0.4, 2);
			drawCube();
		glPopMatrix();

		// right arm
		glPushMatrix();
			glTranslatef(-0.3, 0, -2);
			glScalef(0.4, 0.4, 2);
			drawCube();
		glPopMatrix();

		// left leg
		glPushMatrix();
			glTranslatef(1, 0, 0);
			glRotatef(-20, 0, 1, 0);
			glScalef(0.4, 0.4, 2);
			drawCube();
		glPopMatrix();

		// right leg
		glPushMatrix();
			glTranslatef(-1, 0, 0);
			glRotatef(20, 0, 1, 0);
			glScalef(0.4, 0.4, 2);
			drawCube();
		glPopMatrix();

	glPopMatrix();

	// ****** LIFEBAR ******
	LifeBar *lifebar = new LifeBar();
	Transform * lt = (Transform*)lifebar->getComponentById("transformLifeBar");
	//Transform * e1t_lifebar = (Transform*)e1->getComponentById("transformLifeBar");
	lt->position->x = t->position->x;
	lt->position->y = t->position->y;
	lt->position->z = (t->position->z + 1.2); // ... + val -> above the object

	// change scale->x between 0 and 1 scale->x when lifebar need to be reduced
	lt->scale->x = 0.5;
	lt->scale->y = 0.1;
	lt->scale->z = 0.1;

	lt->rotation->z = t->rotation->z;

	glPushMatrix();
	lifebar->draw();
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

void Player::setUpCollider()
{
	Collider * collider = new Collider(this);
	collider->addBox(
		new Transform::Coordinates(0.5, 0.5, 1.25), 
		new Transform::Coordinates(-0.5, -0.5, -1.25));

	collider->registerOnCollisionEnterCallback(&GameObject::onCollisionEnter);
	addComponent("collider", collider);
}

void Player::onCollisionEnter(GameObject * collidingObject)
{
	printf("Player is colliding!!!");
}

void Player::drawCube()
{
	GLfloat vertices[][3] = { 
		{  0.5,  0.5,  0.5 },
		{ -0.5,  0.5,  0.5 },
		{ -0.5,  0.5, -0.5 },
		{  0.5,  0.5, -0.5 },
		{  0.5, -0.5,  0.5 },
		{ -0.5, -0.5,  0.5 },
		{ -0.5, -0.5, -0.5 },
		{  0.5, -0.5, -0.5 } };

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
}