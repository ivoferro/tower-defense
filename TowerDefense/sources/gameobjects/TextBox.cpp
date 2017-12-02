#include "../../headers/gameobjects/TextBox.h"
#include "../../headers/gameobjects/GameText.h"
#include "../../headers/components/Transform.h"
#include "../../headers/framework/Application.h"

TextBox::TextBox()
{
	addComponent("transform", new Transform());
}

TextBox::~TextBox()
{
}

void TextBox::drawPolygon(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat colors[])
{
	/* draw a polygon via list of vertices */

	Transform* t = (Transform*)getComponentById("transform");

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, Application::instance()->getTextures()->getTexture("vinil2"));

	glBegin(GL_POLYGON);

	glNormal3fv(colors);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2fv(b);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2fv(a);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2fv(c);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2fv(d);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void TextBox::drawBox()
{
	GLfloat width = 0.6f;
	GLfloat height = 1.7f;
	GLfloat vertices[][2] = {
		{ width,  -height },
		{ -width,  -height },
		{ width,  height },
		{ -width,  height }
	};

	GLfloat colors[][3] = { 0,  0,  0 };

	drawPolygon(vertices[0], vertices[1], vertices[2], vertices[3], colors[0]);
}

void TextBox:: draw() {

	Transform * t = (Transform*)getComponentById("transform");

	glPushMatrix();
	glTranslatef(t->position->x, t->position->y, t->position->z);
	glScalef(t->scale->x, t->scale->y, t->scale->z);

	drawBox();

	glPopMatrix();
	isFixed = true;

}

void TextBox:: drawWithText(char* texts[], int size)
{
	int i;
	Transform *previous=0;
	GLfloat blackcolor[3] = { 0,0,0 };
	for (i = 0; i < size; i++) {

		//creating text
		GameText * gameText = new GameText(texts[i]);
		Transform *textT = (Transform*)gameText->getComponentById("transform");

		Transform * t = (Transform*)getComponentById("transform");
		glPushMatrix();
		if (i != 0) {
			//TEXT
			textT->position->x = previous->position->x;
			textT->position->y = previous->position->y -0.3;
			textT->position->z = previous->position->z;
		}
		else {
			//TITLE
			textT->position->x = t->position->x-0.15;
			textT->position->y = t->position->y;
			textT->position->z = t->position->z;
		}

		glTranslatef(textT->position->x, textT->position->y, textT->position->z);

		previous = textT;

		glPopMatrix();
		gameText->setColor(blackcolor);
		gameText->draw();
	}
};