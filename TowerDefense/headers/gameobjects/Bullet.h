#pragma once

#include "../framework/GameObject.h"
#include "../framework/Drawable.h"
#include "../framework/Scene.h"
#include "../../headers/objloader/glm.h"

class Bullet : public GameObject
{

private:
	GLMmodel * bulletModel = NULL;
	Scene * parentScene;
	void setUpCollider();
	void onCollisionEnter(GameObject * collidingObject) override;
	void initModel();

public:
	Bullet(Scene * parentScene);
	~Bullet();

	std::string id;
	GLboolean doRemove = false;

	void draw();

};