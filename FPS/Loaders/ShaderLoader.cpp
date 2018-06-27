#pragma once
#include "ShaderLoader.h"
#include <iostream>
GLuint ShaderLoader::getProgramHandle()
{
	return _programHandle;
}

GLuint ShaderLoader::compileShader(GLenum shader, const char *source)
{
	GLuint shaderHandle = glCreateShader(shader);
	
	glShaderSource(shaderHandle, 1, &source, NULL);
	glCompileShader(shaderHandle);

	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 1) {
		infoLog = new char[infologLength];
		glGetShaderInfoLog(shaderHandle, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		delete[]infoLog;
	}

	return shaderHandle;
}
ShaderLoader::ShaderLoader(const char* sourceVS, const char *sourceFS)
{
	_programHandle = glCreateProgram();

	GLuint vertexShaderHandle = compileShader(GL_VERTEX_SHADER, sourceVS);
	GLuint fragmentShaderHandle = compileShader(GL_FRAGMENT_SHADER, sourceFS);
	
	glAttachShader(_programHandle, vertexShaderHandle);
	glAttachShader(_programHandle, fragmentShaderHandle);

	glLinkProgram(_programHandle);

	//glDeleteShader(vertexShaderHandle);
	//glDeleteShader(fragmentShaderHandle);

	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetShaderiv(_programHandle, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 1) {
		infoLog = new char[infologLength];
		glGetShaderInfoLog(_programHandle, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		delete[]infoLog;
	}

}
ShaderLoader::~ShaderLoader()
{
	glDeleteProgram(_programHandle);
}