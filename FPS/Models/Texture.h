#pragma once
#include "..\Dependencies\glew\glew.h"
#include "..\Loaders\lodepng.h"
#include <vector>
class Texture
{
	GLuint tex;
	GLuint readTexture(char* filename);

public:
	Texture(char *filename);
	~Texture();
	GLuint getTexture();
};