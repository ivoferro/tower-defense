#include "../../headers/components/Transform.h"

Transform::Transform()
{
	position = new Coordinates();
	rotation = new Coordinates();
	scale = new Coordinates(1, 1, 1);
}

Transform::Coordinates::Coordinates()
{
	x = 0;
	y = 0;
	z = 0;
}

Transform::Coordinates::Coordinates(GLfloat x, GLfloat y, GLfloat z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
