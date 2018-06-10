#pragma once
#include <GL/glew.h>
#include <map>
#include <string>
#include "../Loaders/lodepng.h"
#include <iostream>
#include <vector>

class Texture
{
	GLuint tex;
	GLuint readTexture(const char* filename);
	static std::map<std::string, Texture*> texture_cache;

	Texture(const char *filename);
	~Texture();
public:
	
	
	GLuint getTexture();
	static Texture* getTexture(std::string name);
	static void free();
};