#pragma once
#ifndef __VertexData__h
#define __VertexData__h

#include "..\Dependencies\glm\glm.hpp"
class VertexData
{
	
public:
	glm::vec4 postion;
	glm::vec4 normal;
	VertexData(glm::vec3 postion, glm::vec3 normal);
	~VertexData();
};

#endif // !__VertexData__h
