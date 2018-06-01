#include "VertexBuffer.h"
#include <iostream>
#include "VertexData.h"
GLuint VertexBuffer::getVertexBuffer()
{
	return vertexBufferID;
}


void VertexBuffer::configureVertexAttributes(ShaderInterface *shader)
{
	auto vertexPosition = shader->getPostionVertex();
	if (vertexPosition != -1)
	{
		glEnableVertexAttribArray(vertexPosition);
		glVertexAttribPointer(vertexPosition, 4, GL_FLOAT, GL_FALSE, stride, NULL);
	}
	auto normal = shader->getNormal();
	if (normal != -1)
	{
		glEnableVertexAttribArray(normal);
		glVertexAttribPointer(normal, 4, GL_FLOAT, GL_FALSE, stride, ((GLvoid*)(4 * sizeof(GLfloat))));
	}

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
}

void VertexBuffer::renderVertexBuffer()
{
	glDrawArrays(mode, 0, count);
}

VertexBuffer::VertexBuffer(const GLvoid *data, GLsizeiptr size, GLenum mode, GLsizei count, GLsizei stride):
	mode(mode), count(count),stride(stride)
{
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &vertexBufferID);
	vertexBufferID = -1;
}