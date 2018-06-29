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
void ShaderInterface::setVec3(std::string name, glm::vec3 a)
{
	setVec3((char*)name.c_str(), a);
}
void ShaderInterface::setVec3(std::string name, float a, float b, float c)
{
	setVec3((char*)name.c_str(), a, b, c);
}
void ShaderInterface::setVec3(char * name, float a, float b, float c)
{
	auto id = glGetUniformLocation(shader->getProgramHandle(), name);
	glUniform3f(id, a, b, c);

}
void ShaderInterface::setFloat(std::string name, float f)
{
	setFloat((char*)name.c_str(), f);
}
void ShaderInterface::setVec3(char *name, glm::vec3 a)
{
	setVec3(name, a.x, a.y, a.z);
}
void ShaderInterface::setFloat(char *name, float f)
{
	auto id = glGetUniformLocation(shader->getProgramHandle(), name);
	glUniform1f(id, f);
}
void ShaderInterface::setInt(std::string name, int f)
{
	setInt((char*)name.c_str(), f);
}
void ShaderInterface::setInt(char *name, int f)
{
	auto id = glGetUniformLocation(shader->getProgramHandle(), name);
	glUniform1i(id, f);
}
GLint ShaderInterface::getNormal()
{
	return aNormal;
}
GLint ShaderInterface::getTexCoord()
{
	return aTexCoord;
}



ShaderInterface::ShaderInterface(const char * sourceVS, const char * sourceFS)
{
	vertexShader = loadTextFromFile(sourceVS);
	fragmetShader = loadTextFromFile(sourceFS);
	shader = new ShaderLoader(vertexShader, fragmetShader);
	aPostionVertex = glGetAttribLocation(shader->getProgramHandle(), "aPostionVertex");
	aNormal = glGetAttribLocation(shader->getProgramHandle(), "aNormal");
	aTexCoord = glGetAttribLocation(shader->getProgramHandle(), "aTexCoords");
	
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
