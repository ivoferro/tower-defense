#include "../../headers/components/Transform.h"
#include "../../headers/gameobjects/MapObject.h"
#include "../../headers/objloader/glm.h"


MapObject::MapObject(char * path)
{
	this->path = path;

	GLboolean	isInit;
	StudioModel   mdl;   // MDL Model

	addComponent("transform", new Transform());
}


MapObject::~MapObject()
{
}

void MapObject::draw()
{
	initMapObject(path);

	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();
	
	glTranslatef(t->position->x, t->position->y, t->position->z);
	glScalef(t->scale->x, t->scale->y, t->scale->z);
	glRotatef(t->rotation->z, 0, 0, 1);
	
	mdlviewer_display(mdl);
	glPopMatrix();
}

void MapObject::initMapObject(char * path)
{
	if (isInit == GL_FALSE)
	{
		mdlviewer_init(path, mdl);
		isInit = GL_TRUE;
	}
}