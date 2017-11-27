#pragma once

#include "../framework/Component.h"
#include "Transform.h"
#include <list>

class TargetPath : public Component
{

private:
	std::list<Transform::Coordinates *> objectives;

public:
	TargetPath();
	~TargetPath();

	GLboolean isObjectivesEmpty();
	void addObjective(Transform::Coordinates * objective);
	Transform::Coordinates * nextObjective();
	void popCoordinate();
};

