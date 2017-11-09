#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include <list>

class Component
{

private:
	std::list<std::string> tags;

public:
	Component();
	~Component();

	GLboolean addTag(std::string tag);
	GLboolean hasTag(std::string tag);

};