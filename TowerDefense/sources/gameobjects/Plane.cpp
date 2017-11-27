#include "../../headers/gameobjects/Plane.h"
#include "../../headers/components/Transform.h"
#include "../../headers/framework/Application.h"

Plane::Plane(std::string textureID)
{
	this->textureID = textureID;

	addComponent("transform", new Transform());
}

Plane::~Plane()
{
}

void Plane::draw()
{
	Transform * t = (Transform*)getComponentById("transform");
	
	glPushMatrix();

		glTranslatef(t->position->x, t->position->y, t->position->z);
		glRotatef(t->rotation->x, 1, 0, 0);
		glRotatef(t->rotation->y, 0, 1, 0);
		glRotatef(t->rotation->z, 0, 0, 1);
		glScalef(t->scale->x, t->scale->y, t->scale->z);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, Application::instance()->getTextures()->getTexture(textureID));

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.5f, 0.5f, 0.0f);
			glTexCoord2f(1.0f * t->scale->x, 0.0f);
			glVertex3f(-0.5f, 0.5f, 0.0f);
			glTexCoord2f(1.0f * t->scale->x, 1.0f * t->scale->y);
			glVertex3f(-0.5f, -0.5f, 0.0f);
			glTexCoord2f(0.0f, 1.0f * t->scale->y);
			glVertex3f(0.5f, -0.5f, 0.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, NULL);

	glPopMatrix();
}
