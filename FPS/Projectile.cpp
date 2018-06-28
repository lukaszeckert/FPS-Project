#include "Projectile.h"





Projectile::Projectile(Entity * entity, PointLight * pointLight):entity(entity), pointLight(pointLight)
{
	pointLight->active = true;
	ResourceManager::getResourceManager().dynamicsWorld->removeCollisionObject(entity->rigidBody);
	btCollisionShape* cameraShape = new btBoxShape(btVector3(0.1, 0.1, 0.1));
	btDefaultMotionState* cameraMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(entity->position.x, entity->position.y, entity->position.z)));
	btScalar mass = 0.00001;
	btVector3 cameraInertia(0, 0, 0);
	cameraShape->calculateLocalInertia(mass, cameraInertia);
	btRigidBody::btRigidBodyConstructionInfo cameraRigidBodyCI(mass, cameraMotionState, cameraShape, cameraInertia);
	entity->rigidBody = new btRigidBody(cameraRigidBodyCI);
	ResourceManager::getResourceManager().dynamicsWorld->addRigidBody(entity->rigidBody);
}

Projectile::~Projectile()
{
	LightSystem::getLightSystem()->unbind(pointLight);
	pointLight->active = false;
	ResourceManager::getResourceManager().dynamicsWorld->removeCollisionObject(entity->rigidBody);
}