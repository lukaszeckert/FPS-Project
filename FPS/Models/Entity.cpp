#include "Entity.h"


Entity::Entity(glm::vec3 position, VertexBuffer* vertexBuffer, ShaderInterface *shaderInterface): Entity(position, vertexBuffer, shaderInterface, glm::vec3(1.0f))
{
}

Entity::Entity(glm::vec3 position, VertexBuffer * vertexBuffer, ShaderInterface * shaderInterface, glm::vec3 color) : position(position), vertexBuffer(vertexBuffer), shaderInterface(shaderInterface), color(color)
{
}


Entity::~Entity()
{
	
}
