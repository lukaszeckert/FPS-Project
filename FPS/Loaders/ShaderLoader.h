#pragma once
#include "..\Dependencies\glew\glew.h"
#include "..\Dependencies\glfw\glfw3.h"


class ShaderLoader
{
	GLuint _programHandle;

	GLuint compileShader(GLenum shader, const char *source);
public:
	GLuint getProgramHandle();
	ShaderLoader(const char* sourceVS, const char *sourceFS);
	~ShaderLoader();
};