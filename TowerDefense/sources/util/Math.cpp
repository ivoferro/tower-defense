#include "../../headers/util/Math.h"
#include <math.h>

GLfloat Math::radians(GLfloat degrees)
{
	return M_PI * degrees / 180;
}

GLfloat Math::min(GLfloat a, GLfloat b)
{
	return a < b ? a : b;
}

GLfloat Math::max(GLfloat a, GLfloat b)
{
	return a > b ? a : b;
}

Transform::Coordinates * Math::subtract(Transform::Coordinates * p1, Transform::Coordinates * p2)
{
	return new Transform::Coordinates(p1->x-p2->x, p1->y-p2->y, p1->z-p2->z);
}

GLfloat Math::length(Transform::Coordinates * p)
{
	return sqrt((p->x*p->x) + (p->y*p->y) + (p->z*p->z));
}

Transform::Coordinates * Math::normalize(Transform::Coordinates * p)
{
	GLfloat len = length(p);
	return new Transform::Coordinates(p->x/len, p->y/len, p->z/len);
}

GLfloat Math::distance2D(Transform::Coordinates * p1, Transform::Coordinates * p2)
{
	GLfloat xPow = pow((p1->x - p2->x), 2);
	GLfloat yPow = pow((p1->y - p2->y), 2);

	return sqrt(xPow + yPow);
}
