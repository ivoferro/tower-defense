#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../components/Transform.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

class Math
{

public:
	static GLfloat radians(GLfloat degrees);
	static GLfloat min(GLfloat a, GLfloat b);
	static GLfloat max(GLfloat a, GLfloat b);

	static Transform::Coordinates * subtract(Transform::Coordinates * p1, Transform::Coordinates * p2);
	static GLfloat length(Transform::Coordinates * p);
	static Transform::Coordinates * normalize(Transform::Coordinates * p);
	static GLfloat distance2D(Transform::Coordinates * p1, Transform::Coordinates * p2);

};

