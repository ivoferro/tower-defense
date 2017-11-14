#include "../../headers/util/Math.h"

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
