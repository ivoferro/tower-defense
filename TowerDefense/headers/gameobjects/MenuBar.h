#pragma once

#include "../framework/GameObject.h"
#include "../framework/Drawable.h"
#include <map>

class MenuBar : public GameObject, Drawable
{

private:
	GLfloat width;
	GLfloat height;
	char* texture;

	void drawBar();
	void drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat color[]);
	
public:
	MenuBar();
	MenuBar(char* text);
	~MenuBar();
	void draw();
	void drawWithText(char* text, GLfloat color[3]);
};
