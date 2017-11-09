#include "../../headers/components/Transform.h"

Transform::Transform()
{
	position = new Coordinates();
	rotation = new Coordinates();
	scale = new Coordinates();
}

Transform::Coordinates::Coordinates()
{
	x = 0;
	y = 0;
	z = 0;
}
