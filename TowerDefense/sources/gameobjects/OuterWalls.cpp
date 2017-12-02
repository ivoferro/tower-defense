#include "../../headers/gameobjects/OuterWalls.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/Collider.h"
#include "../../headers/util/Illumination.h"

void OuterWalls::setUpCollider()
{
	Collider * collider = new Collider(this);

	collider->addBox(
		new Transform::Coordinates(60, 50, 60),
		new Transform::Coordinates(-60, 100, -60));
	collider->addBox(
		new Transform::Coordinates(60, -50, 60),
		new Transform::Coordinates(-60, -100, -60));
	collider->addBox(
		new Transform::Coordinates(50, 60, 60),
		new Transform::Coordinates(100, -60, -60));
	collider->addBox(
		new Transform::Coordinates(-50, 60, 60),
		new Transform::Coordinates(-100, -60, -60));

	collider->registerOnCollisionEnterCallback(&GameObject::onCollisionEnter);

	addComponent("collider", collider);
}

OuterWalls::OuterWalls()
{
	addComponent("transform", new Transform());
	setUpCollider();
}

OuterWalls::~OuterWalls()
{
}