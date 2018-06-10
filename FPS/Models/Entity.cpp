#include "Entity.h"


Entity::Entity(glm::vec3 position, Object* object, ShaderInterface *shaderInterface): Entity(position, object, shaderInterface, glm::vec3(1.0f))
{
}

Entity::Entity(glm::vec3 position, Object* object, ShaderInterface * shaderInterface, glm::vec3 color) : position(position), object(object), shaderInterface(shaderInterface),scale(glm::vec3(1,1,1)),rotation(0,0,0)
{
	setColor(color);
}



Entity::~Entity()
{
	
}

void Entity::setColor(glm::vec3 color)
{
	for (auto it : object->meshes)
		it->color = color;
}
