#pragma once
#ifndef __VertexData__h
#define __VertexData__h

#include <glm\glm.hpp>
class VertexData
{
	
public:
	glm::vec4 postion;
	glm::vec4 normal;
	glm::vec2 text;
	VertexData(glm::vec3 postion, glm::vec3 normal,glm::vec2 text);
	~VertexData();
};

#endif // !__VertexData__h
