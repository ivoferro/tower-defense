#pragma once

#include "../framework/GameObject.h"
#include "../framework/Drawable.h"


class TextBox : public GameObject, Drawable
{

private:
	void drawBox();
	void drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat color[]);

public:
	TextBox();
	~TextBox();
	void drawWithText(char* texts[], int size);
	void draw();
	GLboolean isFixed = false;
};