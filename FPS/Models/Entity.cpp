#include "Entity.h"
#include "../Managers/ResourceManager.h"

Entity::Entity(glm::vec3 position, Object* object, ShaderInterface *shaderInterface): Entity(position, object, shaderInterface, glm::vec3(1.0f))
{
}

Entity::Entity(glm::vec3 position, Object* object, ShaderInterface * shaderInterface, glm::vec3 color) : position(position), object(object), shaderInterface(shaderInterface),scale(glm::vec3(1,1,1)),rotation(0,0,0),color(color)
{
	// setColor(color);
	// btCollisionShape* shape = new btBoxShape(btVector3(0.5, 0.5, 0.5));
	btDefaultMotionState* motionState =
                new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position.x, position.y, position.z)));
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(0, motionState, object->shape);
	rigidBody = new btRigidBody(rigidBodyCI);
	ResourceManager::getResourceManager().dynamicsWorld->addRigidBody(rigidBody);
}



Entity::~Entity()
{
	
}


