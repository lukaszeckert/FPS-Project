#include "Entity.h"
#include "../Managers/ResourceManager.h"

Entity::Entity(glm::vec3 position, Object* object, ShaderInterface *shaderInterface): Entity(position, object, shaderInterface, glm::vec3(1.0f))
{
}

Entity::Entity(glm::vec3 position, Object* object, ShaderInterface * shaderInterface, glm::vec3 color) : position(position), object(object), shaderInterface(shaderInterface),scale(glm::vec3(1,1,1)),rotation(0,0,0)
{
	setColor(color);
	btCollisionShape* shape = new btSphereShape(1);
	btDefaultMotionState* motionState =
                new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position.x, position.y, position.z)));
	btScalar mass = 1;
	btVector3 inertia(0, 0, 0);
	shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, shape, inertia);
	rigidBody = new btRigidBody(rigidBodyCI);
	ResourceManager::getResourceManager().dynamicsWorld->addRigidBody(rigidBody);
}



Entity::~Entity()
{
	
}

void Entity::setColor(glm::vec3 color)
{
	for (auto it : object->meshes)
		it->color = color;
}
