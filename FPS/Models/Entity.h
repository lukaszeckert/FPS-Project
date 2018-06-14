#pragma once

#include "../Models/VertexBuffer.h"
#include "../Interfaces/ShaderInterface.h"
#include "../Models/Object.h"
#include <glm/glm.hpp>
#include <vector>
#include <bullet/btBulletDynamicsCommon.h>

class Entity
{
	//TODO add textures
	


public:
	Entity(glm::vec3 position, Object* object, ShaderInterface *shaderInterface);
	Entity(glm::vec3 position, Object* object, ShaderInterface *shaderInterface, glm::vec3 color);
	~Entity();
	
	void setColor(glm::vec3 color);
	//VertexBuffer* vertexBuffer;
	Object* object;
	ShaderInterface* shaderInterface;
	btRigidBody* rigidBody;	
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	
	//Material
	//glm::vec3 ambient;
	//glm::vec3 diffuse;
	//glm::vec3 specular;
	//float shiniess;

	//GLuint diffuseMap;
	//GLuint specularMap;
};

