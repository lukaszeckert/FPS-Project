#include "Entity.h"


Entity::Entity(glm::vec3 position, VertexBuffer* vertexBuffer, ShaderInterface *shaderInterface): position(position), vertexBuffer(vertexBuffer),shaderInterface(shaderInterface)
{
}


Entity::~Entity()
{
	
}
