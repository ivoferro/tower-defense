#include "..\..\headers\util\Drawer.h"

void Drawer::drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat d[], GLfloat normal[], GLfloat color[])
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

void Drawer::drawBox(Transform::Coordinates * c1, Transform::Coordinates * c2)
{
	GLfloat xMin = Math::min(c1->x, c2->x);
	GLfloat yMin = Math::min(c1->y, c2->y);
	GLfloat zMin = Math::min(c1->z, c2->z);

	GLfloat xMax = Math::max(c1->x, c2->x);
	GLfloat yMax = Math::max(c1->y, c2->y);
	GLfloat zMax = Math::max(c1->z, c2->z);

	GLfloat vertices[][3] = {
		{ xMax, yMax, zMax },
		{ xMin, yMax, zMax },
		{ xMin, yMax, zMin },
		{ xMax, yMax, zMin },
		{ xMax, yMin, zMax },
		{ xMin, yMin, zMax },
		{ xMin, yMin, zMin },
		{ xMax, yMin, zMin } };

	GLfloat normals[][4] = {
		{ 0,  1,  0 },
		{ -1,  0,  0 },
		{ 0,  -1, 0 },
		{ 1,  0,  0 },
		{ 0,  0,  1 },
		{ 0,  0, -1 } };

	GLfloat color[] = { 0.0f, 1.0f, 0.0f, 1.0f};

	drawPolygon(vertices[0], vertices[3], vertices[2], vertices[1], normals[0], color);
	drawPolygon(vertices[1], vertices[2], vertices[6], vertices[5], normals[1], color);
	drawPolygon(vertices[5], vertices[6], vertices[7], vertices[4], normals[2], color);
	drawPolygon(vertices[4], vertices[7], vertices[3], vertices[0], normals[3], color);
	drawPolygon(vertices[1], vertices[5], vertices[4], vertices[0], normals[4], color);
	drawPolygon(vertices[2], vertices[3], vertices[7], vertices[6], normals[5], color);
}