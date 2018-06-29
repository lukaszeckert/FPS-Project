#pragma once

#include "../Models/VertexBuffer.h"
#include "../Interfaces/ShaderInterface.h"
#include "../Models/Object.h"
#include <glm/glm.hpp>
#include <vector>
#include <bullet/btBulletDynamicsCommon.h>

enum class EntityType {
	PROJECTILE,
	ENEMY,
	OTHER
};

class Entity
{
	//TODO add textures
	

	
public:

	Entity(glm::vec3 position, Object* object, ShaderInterface *shaderInterface, 
		EntityType type = EntityType::OTHER, glm::vec3 rotation = glm::vec3(0, 0, 0));
	Entity(glm::vec3 position, Object* object, ShaderInterface *shaderInterface, 
		glm::vec3 color, EntityType type = EntityType::OTHER, glm::vec3 rotation = glm::vec3(0,0,0));
	~Entity();
	glm::vec3 getPosition();
	void setDataPointer(void * data);
	void * getDataPointer();
	//VertexBuffer* vertexBuffer;
	void *overObject;
	EntityType type;
	Object* object;
	ShaderInterface* shaderInterface;
	btRigidBody* rigidBody;	
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	void* dataPointer;
	glm::vec3 color;
	//Material
	//glm::vec3 ambient;
	//glm::vec3 diffuse;
	//glm::vec3 specular;
	//float shiniess;

	//GLuint diffuseMap;
	//GLuint specularMap;
};