#include "../../headers/framework/Textures.h"

// The function to read jpg files
extern "C" int read_JPEG_file(const char *, char **, int *, int *, int *);

Textures::Textures()
{
	registerTexture("metal_plate", "resources/metal_plate.jpg");
}

Textures::~Textures()
{
	for (std::map<std::string, GLuint*>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		it->second->~GLuint();
	}
}

GLboolean Textures::registerTexture(std::string textureID, char * texturePath)
{
	if (hasTexture(textureID))
	{
		printf("The texture with the ID '%s' already exists.\n", textureID.c_str());
		return false;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	GLuint * texture = new GLuint();
	glGenTextures(1, texture);

	glBindTexture(GL_TEXTURE_2D, *texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	char *image;
	int w, h, bpp;

	if (read_JPEG_file(texturePath, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, *image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("The texture '%s' was not found\n", texturePath);
		return false;
	}
	glBindTexture(GL_TEXTURE_2D, NULL);

	textures[textureID] = texture;
	return true;
}

GLboolean Textures::hasTexture(std::string textureID)
{
	return textures.find(textureID) != textures.end();
}

GLuint Textures::getTexture(std::string textureID)
{
	return *textures[textureID];
}
