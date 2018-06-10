#pragma once
#include <GL/glew.h>
#include "../Loaders/lodepng.h"
#include <vector>
class Texture
{
	GLuint tex;
	GLuint readTexture(const char* filename);

public:
	Texture(const char *filename);
	~Texture();
	GLuint getTexture();
};