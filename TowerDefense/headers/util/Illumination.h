#pragma once

#include <stdlib.h>
#include <GL/glut.h>

class Illumination
{

public:
	static const GLfloat NO_MATERIAL[];
	static const GLfloat MATERIAL_AMBIENT_COLOR[];
	static const GLfloat MATERIAL_SPECULAR[];

	static const GLfloat NO_SHININESS[];
	static const GLfloat LOW_SHININESS[];
	static const GLfloat HIGH_SHININESS[];

	static const GLfloat MATERIAL_EMISSION[];

};

