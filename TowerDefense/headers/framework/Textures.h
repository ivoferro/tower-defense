#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include <map>

class Textures
{

private:
	std::map<std::string, GLuint*> textures;

public:
	Textures();
	~Textures();

	GLboolean registerTexture(std::string textureID, char * texturePath);
	GLboolean hasTexture(std::string textureID);
	GLuint getTexture(std::string textureID);

};