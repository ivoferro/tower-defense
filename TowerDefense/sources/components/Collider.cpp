#include "../../headers/components/Collider.h"
#include "../../headers/util/Math.h"

Collider::Collider(GameObject * parent)
{
	this->parent = parent;
}

Collider::~Collider()
{
}

void Collider::addBox(Transform::Coordinates * C1, Transform::Coordinates * C2)
{
	boxes.push_front(std::make_pair(C1, C2));
}

std::list<std::pair<Transform::Coordinates*, Transform::Coordinates*>> Collider::getBoxes()
{
	return std::list<std::pair<Transform::Coordinates*, Transform::Coordinates*>>(boxes);
}

void Collider::testCollision(GameObject * otherObject)
{
	if (doCollide(otherObject))
	{
		onCollisionEnterCallback(otherObject);
	}
}

GLboolean Collider::doCollide(GameObject * otherObject)
{
	if (!otherObject->hasComponent("collider"))
	{
		return false;
	}

	std::list<std::pair<Transform::Coordinates*, Transform::Coordinates*>> otherBoxes
		= ((Collider*)(otherObject->getComponentById("collider")))->getBoxes();

	for (const std::pair<Transform::Coordinates*, Transform::Coordinates*> box : boxes)
	{
		GLfloat ac1[] = { std::get<0>(box)->x, std::get<0>(box)->y, std::get<0>(box)->z };
		GLfloat ac2[] = { std::get<1>(box)->x, std::get<1>(box)->y, std::get<1>(box)->z };
		for (const std::pair<Transform::Coordinates*, Transform::Coordinates*> otherBox : otherBoxes)
		{
			GLfloat bc1[] = { std::get<0>(otherBox)->x, std::get<0>(otherBox)->y, std::get<0>(otherBox)->z };
			GLfloat bc2[] = { std::get<1>(otherBox)->x, std::get<1>(otherBox)->y, std::get<1>(otherBox)->z };

			if (doCollide(ac1, ac2, bc1, bc2))
			{
				return true;
			}
		}
	}
	return false;
}

void Collider::registerOnCollisionEnterCallback(void(*OnCollisionEnterCallback)(GameObject *collidingObject))
{
	this->onCollisionEnterCallback = OnCollisionEnterCallback;
}

GLboolean Collider::doCollide(GLfloat * ac1, GLfloat * ac2, GLfloat * bc1, GLfloat * bc2)
{
	for (size_t i = 0; i < 3; i++) // loop dimensions
	{
		GLfloat aMin = Math::min(ac1[i], ac2[i]);
		GLfloat aMax = Math::max(ac1[i], ac2[i]);
		GLfloat bMin = Math::min(ac1[i], ac2[i]);
		GLfloat bMax = Math::max(ac1[i], ac2[i]);

		if (aMin > bMax || aMax < bMax)
		{
			return false;
		}
	}
	return true;
}