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

void TargetPath::addObjective(Transform::Coordinates * objective)
{
	objectives.push_back(objective);
}

Transform::Coordinates * TargetPath::nextObjective()
{
	Transform::Coordinates * nextObjective = objectives.front();
	objectives.pop_front();
	return nextObjective;
}