#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "ShaderLoader.h"
#include <stdio.h>
#include <stdlib.h>

class ShaderInterface
{
	ShaderLoader *shader;

	GLint aPostionVertex;
	GLint uColor;
	GLint uP;
	GLint uM;
	GLint uV;
	GLint aNormal;

	char *vertexShader;
	char *fragmetShader;
	char *loadTextFromFile(const char *file);
public:

	GLuint getShader();

	GLint getP();
	GLint getM();
	GLint getV();
	
	GLint getPostionVertex();
	GLint getNormal();
	GLint getColor();

	ShaderInterface(const char *sourceVS, const char *sourceFS);
	~ShaderInterface();
};

