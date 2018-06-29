#include "Entity.h"
#include "../Managers/ResourceManager.h"

Entity::Entity(glm::vec3 position, Object* object, ShaderInterface *shaderInterface, EntityType type, glm::vec3 rotation):
	Entity(position, object, shaderInterface, glm::vec3(1.0f), type, rotation)
{
}

Entity::Entity(glm::vec3 position, Object* object, ShaderInterface * shaderInterface, 
	glm::vec3 color, EntityType type, glm::vec3 rotatation) 
	: position(position), object(object), shaderInterface(shaderInterface),scale(glm::vec3(1,1,1)),rotation(rotatation),color(color),
		type(type)
{

	btQuaternion quat;
	quat.setEuler(rotatation.y, rotatation.x, rotatation.z);
	// setColor(color);
	// btCollisionShape* shape = new btBoxShape(btVector3(0.5, 0.5, 0.5));
	btDefaultMotionState* motionState =
                new btDefaultMotionState(btTransform(quat, btVector3(position.x, position.y, position.z)));
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(0, motionState, object->shape);
	rigidBody = new btRigidBody(rigidBodyCI);
	rigidBody->setUserPointer(this);
	
	
	ResourceManager::getResourceManager().dynamicsWorld->addRigidBody(rigidBody,1,1);
}



Entity::~Entity()
{
	ResourceManager::getResourceManager().dynamicsWorld->removeCollisionObject(rigidBody);
	delete rigidBody->getMotionState();
}

glm::vec3 Entity::getPosition()
{
	btVector3 &vec = rigidBody->getWorldTransform().getOrigin();
	return glm::vec3(vec.x(), vec.y(), vec.z());
	return glm::vec3();
}
void Entity::setDataPointer(void* data)
{
	dataPointer = data;
}
void* Entity::getDataPointer()
{
	return dataPointer;
}


