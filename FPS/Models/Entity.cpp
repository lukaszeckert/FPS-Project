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
	
	
	ResourceManager::getResourceManager().dynamicsWorld->addRigidBody(rigidBody);
}



Entity::~Entity()
{
	
}


