#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "..\Loaders\ShaderLoader.h"
#include "..\Dependencies\glm\glm.hpp"
#include <stdio.h>
#include <stdlib.h>

class ShaderInterface
{
	ShaderLoader *shader;

	GLint aPostionVertex;
	GLint uColor;
	GLint aTexCoord;

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
	GLint getTexCoord();
	GLint getColor();
	void setVec3(char *name, float a, float b, float c);
	void setFloat(char * name, float f);
	void setInt(char * name, int f);
	void setVec3(char *name, glm::vec3 a);
	

	ShaderInterface(const char *sourceVS, const char *sourceFS);
	~ShaderInterface();
};

