#include "../../headers/gameobjects/Tower.h"
#include "../../headers/components/Transform.h"
#include "../../headers/gameobjects/LifeBar.h"

Tower::Tower()
{
	addComponent("transform", new Transform());
}

Tower::~Tower()
{
}

void Tower::draw()
{
	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();
		glTranslatef(t->position->x, t->position->y, t->position->z);
		glRotatef(t->rotation->z, 0, 0, 1);
		glScalef(3, 3, 3);
		drawTower();
	glPopMatrix();

	// ****** LIFEBAR ******
	LifeBar *lifebar = new LifeBar();
	Transform * lt = (Transform*)lifebar->getComponentById("transformLifeBar");
	//Transform * e1t_lifebar = (Transform*)e1->getComponentById("transformLifeBar");
	lt->position->x = t->position->x;
	lt->position->y = t->position->y;
	lt->position->z = (t->position->z + 6.2); // ... + val -> above the object

	// change scale->x between 0 and 1 scale->x when lifebar need to be reduced
	lt->scale->x = 0.2;
	lt->scale->y = 0.1;
	lt->scale->z = 0.1;

	glPushMatrix();
	lifebar->draw();
	glPopMatrix();
}

void Tower::drawTower()
{
	glBegin(GL_TRIANGLES);

	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(0, 0, 2);
	glVertex3f(0, -0.5, 1);
	glVertex3f(0.5, 0, 1);

	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0, 0, 2);
	glVertex3f(0.5, 0, 1);
	glVertex3f(0, 0.5, 1);

	glColor3f(0.2f, 0.5f, 0.8f);
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0.5, 1);
	glVertex3f(-0.5, 0, 1);


	glColor3f(0.7f, 0.2f, 0.4f);
	glVertex3f(0, 0, 2);
	glVertex3f(-0.5, 0, 1);
	glVertex3f(0, -0.5, 1);
	glEnd();

	glBegin(GL_TRIANGLES);

	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, -0.5, 1);
	glVertex3f(0.5, 0, 1);

	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(0, 0, 0);
	glVertex3f(0.5, 0, 1);
	glVertex3f(0, 0.5, 1);

	glColor3f(0.7f, 0.2f, 0.4f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.5, 1);
	glVertex3f(-0.5, 0, 1);

	glColor3f(0.2f, 0.5f, 0.8f);
	glVertex3f(0, 0, 0);
	glVertex3f(-0.5, 0, 1);
	glVertex3f(0, -0.5, 1);

	glEnd();
}

