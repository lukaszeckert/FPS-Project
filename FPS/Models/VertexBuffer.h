#pragma once
#include "..\Dependencies\glew\glew.h"
#include "..\Dependencies\glfw\glfw3.h"
#include "..\Interfaces\ShaderInterface.h"

class VertexBuffer
{
	GLuint vertexBufferID;
	

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