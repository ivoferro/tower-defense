#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/Component.h"
#include "../framework/GameObject.h"
#include "Transform.h"

class Collider : public Component
{

private:
	GameObject * parent;

	// The boxes colliders stored with two opposite corners
	std::list<std::pair<Transform::Coordinates*, Transform::Coordinates*>> boxes;

	// Callback to be called when a collision happens
	void (GameObject::*onCollisionEnterCallback) (GameObject * collidingObject);

	GLboolean doCollide(GLfloat * ac1, GLfloat * ac2, GLfloat * bc1, GLfloat * bc2);

	void triggerCollisionCallback(GameObject * collidingObject);

public:
	Collider(GameObject * parent);
	~Collider();

	// C1 and C2 are oposite corners
	// Their positions are relative to the origin (0x;0y;0z)
	void addBox(Transform::Coordinates * C1, Transform::Coordinates * C2);

	std::list<std::pair<Transform::Coordinates*, Transform::Coordinates*>> getBoxes();

	// If there is a collision, the onCollisionEnter callback is called
	void testCollision(GameObject * otherObject);

	// True if there is a collision, false otherwise
	// Does NOT call the onCollisionEnter no matter what
	GLboolean doCollide(GameObject * otherObject);

	void registerOnCollisionEnterCallback(void (GameObject::*OnCollisionEnterCallback) (GameObject * collidingObject));

};