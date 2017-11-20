#include "../../headers/framework/Textures.h"

// The function to read jpg files
extern "C" int read_JPEG_file(const char *, char **, int *, int *, int *);

Textures::Textures()
{
}

Textures::~Textures()
{
}

GLboolean Textures::registerTexture(std::string textureID, char * texturePath)
{
	if (hasTexture(textureID))
	{
		printf("The texture with the ID '%s' already exists.\n", textureID.c_str());
		return false;
	}

	glEnable(GL_TEXTURE_2D);

	GLuint tex;
	glGenTextures(1, &tex);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	char *image;
	int w, h, bpp;

	if (read_JPEG_file(texturePath, &image, &w, &h, &bpp))
	{
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	else {
		printf("The texture '%s' was not found\n", texturePath);
		return false;
	}
	glBindTexture(GL_TEXTURE_2D, NULL);

	textures[textureID] = tex;
	return true;
}

GLboolean Textures::hasTexture(std::string textureID)
{
	return textures.find(textureID) != textures.end();
}

GLuint Textures::getTexture(std::string textureID)
{
	return textures[textureID];
}
