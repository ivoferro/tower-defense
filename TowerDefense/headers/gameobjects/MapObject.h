#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "../framework/GameObject.h"
#include "../framework/Drawable.h"
#include "../../headers/mdlloader/Mdlloader.h"
#include "../../headers/mdlloader/studio.h"

class MapObject : public GameObject, Drawable
{

private: 
	char * path;
	GLboolean	isInit;
	StudioModel   mdl;
	void initMapObject(char * path);

public:
	MapObject(char * path);
	~MapObject();
	void draw();
};

