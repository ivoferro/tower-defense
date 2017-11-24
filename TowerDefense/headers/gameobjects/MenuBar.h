#pragma once

#include "../framework/GameObject.h"
#include "../framework/Drawable.h"

class MenuBar : public GameObject, Drawable
{
private:
	void drawBar();
	void drawBarOver();
	void drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat color[]);
	void drawPolygonOver(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat color[]);

public:
	MenuBar();
	~MenuBar();
	void draw();
	void changeColor();
};
