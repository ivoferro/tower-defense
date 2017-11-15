#pragma once

#include "../framework/GameObject.h"

class MenuBar : public GameObject
{
private:
	void drawBar();
	void drawBarOver();
	void drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat color[]);

public:
	MenuBar();
	~MenuBar();
	void draw();
	void changeColor();
};
