#pragma once

#include "../components/Transform.h"
#include "Math.h"
#include "Illumination.h"

class Drawer
{

private:
	static void drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat d[], GLfloat normal[], GLfloat color[]);

public:
	static void drawBox(Transform::Coordinates * c1, Transform::Coordinates * c2);

};

