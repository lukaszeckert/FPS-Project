#pragma once

#include "..\Models\VertexBuffer.h"
#include "..\Interfaces\ShaderInterface.h"
#include "..\Dependencies\glm\glm.hpp"
#include <vector>
class Entity
{
	//TODO add textures
	


public:
	Entity(glm::vec3 position, VertexBuffer* vertexBuffer, ShaderInterface *shaderInterface);
	~Entity();
	
	VertexBuffer* vertexBuffer;
	ShaderInterface* shaderInterface;
	glm::vec3 position;
	//TODO load from obj file
};

