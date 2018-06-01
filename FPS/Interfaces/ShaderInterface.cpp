#include "ShaderInterface.h"
#include <iostream>


char * ShaderInterface::loadTextFromFile(const char * file)
{
	FILE *current = fopen(file,"r");

	fseek(current, 0, SEEK_END);
	int count = (int)ftell(current);
	rewind(current);
	char *data = (char *)malloc(sizeof(char)*count+1);
	count = (int)fread(data, sizeof(char), count, current);
	data[count] = '\0';

	fclose(current);

	return data;
}

GLuint ShaderInterface::getShader()
{
	return shader->getProgramHandle();
}

GLint ShaderInterface::getP()
{
	return uP;
}

GLint ShaderInterface::getM()
{
	return uM;
}

GLint ShaderInterface::getV()
{
	return uV;
}

GLint ShaderInterface::getPostionVertex()
{
	return aPostionVertex;
}

GLint ShaderInterface::getColor()
{
	return uColor;
}
GLint ShaderInterface::getNormal()
{
	return aNormal;
}



ShaderInterface::ShaderInterface(const char * sourceVS, const char * sourceFS)
{
	vertexShader = loadTextFromFile(sourceVS);
	fragmetShader = loadTextFromFile(sourceFS);
	shader = new ShaderLoader(vertexShader, fragmetShader);
	aPostionVertex = glGetAttribLocation(shader->getProgramHandle(), "aPostionVertex");
	aNormal = glGetAttribLocation(shader->getProgramHandle(), "aNormal");
	
	uColor = glGetUniformLocation(shader->getProgramHandle(), "uColor");
	uP = glGetUniformLocation(shader->getProgramHandle(), "P");
	uV = glGetUniformLocation(shader->getProgramHandle(), "V");
	uM = glGetUniformLocation(shader->getProgramHandle(), "M");
	
}

ShaderInterface::~ShaderInterface()
{

	free(vertexShader);
	free(fragmetShader);
	delete shader;
}
