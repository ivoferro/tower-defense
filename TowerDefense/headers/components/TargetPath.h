#pragma once

#include "Transform.h"
#include <list>

class TargetPath
{

private:
	std::list<Transform::Coordinates *> objectives;

public:
	TargetPath();
	~TargetPath();

	void addObjective(Transform::Coordinates * objective);
	Transform::Coordinates * nextObjective();
};

