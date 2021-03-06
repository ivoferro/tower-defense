#include "../../headers/gameobjects/LifeBar.h"
#include "../../headers/components/Transform.h"
#include "../../headers/util/Illumination.h"

LifeBar::LifeBar(GameObject * parent, GLfloat offSetUp, GLfloat rotationOffSet)
{
	this->parent = parent;
	this->offSetUp = offSetUp;
	this->rotationOffSet = rotationOffSet;
}

LifeBar::~LifeBar()
{
}

void LifeBar::drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat normal[], GLfloat color[])
{
	glBegin(GL_POLYGON);

	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Illumination::NO_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SHININESS, Illumination::NO_SHININESS);
	glMaterialfv(GL_FRONT, GL_EMISSION, Illumination::NO_MATERIAL);

	glNormal3fv(normal);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);

	glEnd();
}

void LifeBar::drawLifeBar(GLfloat color[])
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
		{ 0,  1,  0 },
		{ -1,  0,  0 },
		{ 0,  -1, 0 },
		{ 1,  0,  0 },
		{ 0,  0,  1 },
		{ 0,  0, -1 } };

	drawPolygon(vertices[0], vertices[3], vertices[2], vertices[1], normals[0], color);
	drawPolygon(vertices[1], vertices[2], vertices[6], vertices[5], normals[1], color);
	drawPolygon(vertices[5], vertices[6], vertices[7], vertices[4], normals[2], color);
	drawPolygon(vertices[4], vertices[7], vertices[3], vertices[0], normals[3], color);
	drawPolygon(vertices[1], vertices[5], vertices[4], vertices[0], normals[4], color);
	drawPolygon(vertices[2], vertices[3], vertices[7], vertices[6], normals[5], color);
}

void LifeBar::draw()
{
	GLfloat greencolor[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat blackcolor[] = { 0.0, 0.0, 0.0, 1.0 };
	
	Transform * parentTransform = (Transform*)parent->getComponentById("transform");
	Life * life = (Life*)parent->getComponentById("life");
	GLfloat currentPercentage = life->health / life->maxHealth;

	glPushMatrix();
		glTranslatef(parentTransform->position->x, parentTransform->position->y, parentTransform->position->z + offSetUp);
		glRotatef(parentTransform->rotation->z + rotationOffSet, 0, 0, 1);

		glPushMatrix();
			glScalef(1.1f, 0.09, 0.09);
			drawLifeBar(blackcolor);
		glPopMatrix();

		if (life->health > 0)
		{
			glPushMatrix();
				glScalef(currentPercentage, 0.1f, 0.1f);
				drawLifeBar(greencolor);
			glPopMatrix();
		}
	glPopMatrix();
}