#include "../../headers/components/TargetPath.h"

TargetPath::TargetPath()
{
}

TargetPath::~TargetPath()
{
	for (std::list<Transform::Coordinates*>::iterator it = objectives.begin(); it != objectives.end(); ++it)
	{
		(*it)->~Coordinates();
	}
}

GLboolean TargetPath::isObjectivesEmpty()
{
	return objectives.empty();
}

void TargetPath::addObjective(Transform::Coordinates * objective)
{
	objectives.push_back(objective);
}

Transform::Coordinates * TargetPath::nextObjective()
{
	return objectives.front();
}

void TargetPath::popCoordinate()
{
	objectives.pop_front();
}
