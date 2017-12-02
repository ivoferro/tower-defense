#include "..\..\headers\gameobjects\SkyBox.h"
#include "../../headers/framework/Application.h"

void SkyBox::drawBack()
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, Application::instance()->getTextures()->getTexture("back"));

	glBegin(GL_QUADS);

	GLfloat vertices[][3] = {
		{ -51.0f,  51.0f,  25.0f },
		{ -51.0f,  51.0f,  0.0f },
		{ 51.0f,  51.0f,  0.0f },
		{ 51.0f,  51.0f,  25.0f }
	};

	GLfloat normal[] = { 0.0f,  -1.0f,  0.0f };

	glNormal3fv(normal);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(vertices[0]);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(vertices[1]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(vertices[2]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(vertices[3]);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void SkyBox::drawFront()
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, Application::instance()->getTextures()->getTexture("front"));

	glBegin(GL_QUADS);

	GLfloat vertices[][3] = {
		{ 51.0f,  -51.0f,  25.0f },
		{ 51.0f,  -51.0f, 0.0f },
		{ -51.0f,  -51.0f,  0.0f },
		{ -51.0f,  -51.0f,  25.0f }
	};

	GLfloat normal[] = { 0.0f,  -1.0f,  0.0f };

	glNormal3fv(normal);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(vertices[0]);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(vertices[1]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(vertices[2]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(vertices[3]);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void SkyBox::drawLeft()
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, Application::instance()->getTextures()->getTexture("left"));

	glBegin(GL_QUADS);

	GLfloat vertices[][3] = {
		{ 51.0f, 51.0f, 25.0f },
		{ 51.0f, 51.0f, 0.0f },
		{ 51.0f, -51.0f, 0.0f },
		{ 51.0f, -51.0f, 25.0f },
	};

	GLfloat normal[] = { 0.0f,  -1.0f,  0.0f };

	glNormal3fv(normal);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(vertices[0]);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(vertices[1]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(vertices[2]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(vertices[3]);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void SkyBox::drawRight()
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, Application::instance()->getTextures()->getTexture("right"));

	glBegin(GL_QUADS);

	GLfloat vertices[][3] = {
		{ -51.0f, -51.0f, 25.0f },
		{ -51.0f, -51.0f, 0.0f },
		{ -51.0f, 51.0f, 0.0f },
		{ -51.0f, 51.0f, 25.0f }
	};

	GLfloat normal[] = { 0.0f,  -1.0f,  0.0f };

	glNormal3fv(normal);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(vertices[0]);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(vertices[1]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(vertices[2]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(vertices[3]);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void SkyBox::drawUp()
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, Application::instance()->getTextures()->getTexture("up"));

	glBegin(GL_QUADS);

	GLfloat vertices[][3] = {
		{ 51.0f, -51.0f, 25.0f },
		{ -51.0f, -51.0f, 25.0f },
		{ -51.0f, 51.0f, 25.0f },
		{ 51.0f, 51.0f, 25.0f }
	};

	GLfloat normal[] = { 0.0f,  -1.0f,  0.0f };

	glNormal3fv(normal);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(vertices[0]);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(vertices[1]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(vertices[2]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(vertices[3]);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);
}

SkyBox::SkyBox()
{
}

SkyBox::~SkyBox()
{
}

void SkyBox::draw()
{
	if (!Application::instance()->getTextures()->areTexturesLoaded)
	{
		return;
	}

	glPushMatrix();
		drawBack();
		drawFront();
		drawLeft();
		drawRight();
		drawUp();
	glPopMatrix();
}