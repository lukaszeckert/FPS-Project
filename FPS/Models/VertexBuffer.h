#pragma once
#include <glew/glew.h>
#include <glfw/glfw3.h>
#include "../Interfaces/ShaderInterface.h"

class VertexBuffer
{
	GLuint vertexBufferID;
	
	GLuint vao;
	GLenum mode;
	GLsizei count;
	GLsizei stride;

public:

	VertexBuffer(const GLvoid *data, GLsizeiptr size, GLenum mode, GLsizei count,GLsizei stride);
	~VertexBuffer();

	GLuint getVertexBuffer();

	void configureVertexAttributes(ShaderInterface *shader);
	void renderVertexBuffer();
};