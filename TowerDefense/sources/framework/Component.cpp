#include "../../headers/framework/Component.h"

Component::Component()
{
}

Component::~Component()
{
}

GLboolean Component::addTag(std::string tag)
{
	if (hasTag(tag))
	{
		return false;
	}

	tags.push_back(tag);
	return true;
}

GLboolean Component::hasTag(std::string tag)
{
	return std::find(tags.begin(), tags.end(), tag) != tags.end();
}