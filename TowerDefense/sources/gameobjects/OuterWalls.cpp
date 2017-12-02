#include "../../headers/gameobjects/OuterWalls.h"
#include "../../headers/components/Transform.h"
#include "../../headers/components/Collider.h"
#include "../../headers/util/Illumination.h"

void OuterWalls::setUpCollider()
{
	// The colliders of the static objects
	Collider * collider = new Collider(this);

	//  The outer invisivel walls
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

	// brown barreal
	collider->addBox(
		new Transform::Coordinates(51, 17, 4),
		new Transform::Coordinates(48.5, 14.5, -2));

	// camion + rock
	collider->addBox(
		new Transform::Coordinates(12.5, -34, 3),
		new Transform::Coordinates(-6, -40.5, -3));

	// range tower (no need, it has a open area below)
	/*collider->addBox(
		new Transform::Coordinates(13, -38, 3),
		new Transform::Coordinates(2, -50, -3));*/

	// oil barrel
	collider->addBox(
		new Transform::Coordinates(50, 50, 3),
		new Transform::Coordinates(45, 45, -3));

	// christmas tree + sandbags + outdoors kiosk
	collider->addBox(
		new Transform::Coordinates(12.5, -21.5, 3),
		new Transform::Coordinates(5.5, -35, -3));

	// train 1 + train 2
	collider->addBox(
		new Transform::Coordinates(-5, 19, 3),
		new Transform::Coordinates(-50, 12.5, -3));
	
	// mobile office 1, 2, 3
	collider->addBox(
		new Transform::Coordinates(-14, -3, 3),
		new Transform::Coordinates(-23, -50, -3));

	// mobile office 4
	collider->addBox(
		new Transform::Coordinates(-20, -3, 3),
		new Transform::Coordinates(-38, -12, -3));

	// halftrack us
	collider->addBox(
		new Transform::Coordinates(-4, 34.5, 5),
		new Transform::Coordinates(-10, 16.5, -3));

	// military tent
	collider->addBox(
		new Transform::Coordinates(-32, 42, 3),
		new Transform::Coordinates(-50, 40.5, -3));
	collider->addBox(
		new Transform::Coordinates(-32, 31, 3),
		new Transform::Coordinates(-50, 29.5, -3));

	// AA tent
	collider->addBox(
		new Transform::Coordinates(-33, -24, 3),
		new Transform::Coordinates(-50, -35, -3));
	collider->addBox(
		new Transform::Coordinates(-28.5, -27, 3),
		new Transform::Coordinates(-33, -32, -3));

	// house zd + maniak_garage 1 + maniak_garage 2
	collider->addBox(
		new Transform::Coordinates(44, -11.5, 3),
		new Transform::Coordinates(27.5, -50, -3));

	// cop car
	collider->addBox(
		new Transform::Coordinates(12, -9.5, 3),
		new Transform::Coordinates(8, -19, -3));

	// tank (jagd)
	collider->addBox(
		new Transform::Coordinates(50, 9.5, 3),
		new Transform::Coordinates(37.5, 2.5, -3));

	// old pickup
	collider->addBox(
		new Transform::Coordinates(2, 50, 3),
		new Transform::Coordinates(-11, 45, -3));

	// metal plate
	collider->addBox(
		new Transform::Coordinates(36, 41, 3),
		new Transform::Coordinates(15.5, 20.5, -3));


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