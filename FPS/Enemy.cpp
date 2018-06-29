#include "Enemy.h"





void Enemy::lookAt(glm::vec3 position)
{
	entity->rigidBody->activate(true);
	glm::vec3 glmNewLook = position - entity->position;
	glmNewLook.y = 0;
	glm::normalize(glmNewLook);
	btVector3 newLook(glmNewLook.x, glmNewLook.y, glmNewLook.z);
	// assume that "forward" for the player in local-frame is +zAxis
	// and that the player is constrained to rotate about yAxis (+yAxis is "up")
	btVector3 localLook(0, 0, 1); // zAxis
	btVector3 rotationAxis(0.0f, 1.0f, 0.0f); // yAxis

											  // compute currentLook and angle
	btTransform transform = entity->rigidBody->getCenterOfMassTransform();
	btQuaternion rotation = transform.getRotation();
	//btVector3 a = rotation*localLook;
	btVector3 currentLook = btMatrix3x3(rotation)*localLook;// quatRotate(rotation, localLook);//btVector3(rotation[3] * localLook.x() + rotation.y() * localLook.z() - rotation.z() * localLook.y(),
		//rotation[3] * localLook.y() + rotation.z() * localLook.x() - rotation.x() * localLook.z(),
		//rotation[3] * localLook.z() + rotation.x() * localLook.y() - rotation.y() * localLook.x());
		//-rotation.x() * localLook.x() - rotation.y() * localLook.y() - rotation.z() * localLook.z());;
	currentLook = localLook;
	currentLook.setY(0.0f);
	currentLook.normalize();
	btScalar angle = currentLook.angle(newLook);
	// compute new rotation
	auto c = currentLook.cross(newLook);
	btQuaternion newRotation;
	if (c.y() > 0) {
		btQuaternion deltaRotation(rotationAxis, angle);
		newRotation = deltaRotation;
	}
	else
	{
		btQuaternion deltaRotation(rotationAxis, -angle);
		newRotation = deltaRotation;

	}
	
	// apply new rotation
	auto t = btTransform(btQuaternion(0, 0, 0, 1), btVector3(entity->position.x, entity->position.y, entity->position.z));
	t.setRotation(newRotation);
	entity->rigidBody->setCenterOfMassTransform(t);
}

bool Enemy::canShoot(glm::vec3 position)
{
	return false;
	btVector3 End(position.x, position.y, position.z);
	btVector3 Start(entity->rigidBody->getWorldTransform().getOrigin());
	btCollisionWorld::ClosestRayResultCallback RayCallback(Start, End);

	// Perform raycast
	
	ResourceManager::getResourceManager().dynamicsWorld->rayTest(Start, End, RayCallback);

	if (RayCallback.hasHit()) {
		auto newEnd = RayCallback.m_hitPointWorld;
		if (newEnd.distance(End) < 1)
			return true;
		return false;
	}
	return true;
}

Enemy::Enemy(Entity * entity, float hp) :entity(entity), hp(hp), remainingReloadTime(0)
{
	entity->overObject = this;
	ResourceManager::getResourceManager().dynamicsWorld->removeCollisionObject(entity->rigidBody);
	btCollisionShape* cameraShape = new btBoxShape(btVector3(0.3, 0.1, 0.3));
	btDefaultMotionState* cameraMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(entity->position.x, entity->position.y, entity->position.z)));
	btScalar mass = 0.00001;
	btVector3 cameraInertia(0, 0, 0);
	cameraShape->calculateLocalInertia(mass, cameraInertia);
	btRigidBody::btRigidBodyConstructionInfo cameraRigidBodyCI(mass, cameraMotionState, cameraShape, cameraInertia);
	entity->rigidBody = new btRigidBody(cameraRigidBodyCI);
	entity->rigidBody->setUserPointer(entity);
	ResourceManager::getResourceManager().dynamicsWorld->addRigidBody(entity->rigidBody);
}

Enemy::~Enemy()
{
	ResourceManager::getResourceManager().removeEntity(entity);

}

void Enemy::update(float dTime)
{
	remainingReloadTime = std::max(0.0f, remainingReloadTime - dTime);
	auto camera = ResourceManager::getResourceManager().getCamera();
	lookAt(camera->getPosition());
	if (canShoot(camera->getPosition()))
	{
		ProjectileManager::getProjectileManager().createProjectile(entity->getPosition(), camera->getPosition() - entity->getPosition(), 50, glm::vec3(1.0f, 0.0f, 0.0f));
	}
}
