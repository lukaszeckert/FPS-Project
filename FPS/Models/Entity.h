#pragma once

#include "../Models/VertexBuffer.h"
#include "../Interfaces/ShaderInterface.h"
#include <glm/glm.hpp>
#include <vector>
class Entity
{
	//TODO add textures
	


public:
	Entity(glm::vec3 position, VertexBuffer* vertexBuffer, ShaderInterface *shaderInterface);
	Entity(glm::vec3 position, VertexBuffer* vertexBuffer, ShaderInterface *shaderInterface, glm::vec3 color);
	~Entity();
	
	VertexBuffer* vertexBuffer;
	ShaderInterface* shaderInterface;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	glm::vec3 color;

	//Material
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shiniess;

	GLuint diffuseMap;
};

