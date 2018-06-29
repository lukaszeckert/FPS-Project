#include "ResourceManager.h"
#include "../ProjectileManager.h"

void tickCallback(btDynamicsWorld *world, btScalar timeStep) {
	int numManifolds = world->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++)
	{
			btPersistentManifold* contactManifold =  world->getDispatcher()->getManifoldByIndexInternal(i);
			const btCollisionObject* obA = contactManifold->getBody0();
			const btCollisionObject* obB = contactManifold->getBody1();

			int numContacts = contactManifold->getNumContacts();
			for (int j = 0; j < numContacts; j++)
			{
					btManifoldPoint& pt = contactManifold->getContactPoint(j);
					Entity *a = (Entity *)(obA->getUserPointer());
					Entity *b = (Entity *)(obB->getUserPointer());
					if(a != nullptr && b != nullptr) {
						if (pt.getDistance() < 0.f)
						{
								if(a->type == EntityType::PROJECTILE) {
									Projectile *projectile = (Projectile *)(a->overObject);
									ProjectileManager::getProjectileManager().destoryProjectile(projectile);
									if(b->type == EntityType::ENEMY) {

									}
								} else if(b->type == EntityType::PROJECTILE) {
									Projectile *projectile = (Projectile *)(b->overObject);
									ProjectileManager::getProjectileManager().destoryProjectile(projectile);
									if(a->type == EntityType::ENEMY) {

									}
								}
						}
					}
			}
	}
}


ResourceManager *ResourceManager::resourceManager = nullptr;
ResourceManager::ResourceManager()
{
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();;
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -10, 0));
	dynamicsWorld->setInternalTickCallback(tickCallback);

	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -0.2, 0)));
	btRigidBody::btRigidBodyConstructionInfo
					groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);


	shaderArray = new std::vector<ShaderInterface*>();
	EntityArray = new std::vector<Entity*>();
	TextureArray = new std::vector<Texture*>();
	ObjectArray = new std::vector<Object*>();
	lightSystem = LightSystem::getLightSystem();
}


ResourceManager::~ResourceManager()
{
	for (auto it = shaderArray->begin(); it != shaderArray->end(); ++it)
		delete (*it);
	for (auto it = EntityArray->begin(); it != EntityArray->end(); ++it)
		delete (*it);

	for(auto it = ObjectArray->begin(); it != ObjectArray->end(); ++it)
		delete (*it);
	delete shaderArray;
	delete EntityArray;
	delete ObjectArray;

	LightSystem::destroyLightSystem();

}

std::vector<ShaderInterface*>* ResourceManager::getShaderArray()
{
	return shaderArray;
}

std::vector<Entity *>* ResourceManager::getEntityArray()
{
	return EntityArray;
}
std::vector<Texture*>* ResourceManager::getTextureArray()
{
	return TextureArray;
}
std::vector<Object*>* ResourceManager::getObjectArray()
{
	return ObjectArray;
}
ResourceManager & ResourceManager::getResourceManager()
{
	if (resourceManager == nullptr)
	{
		resourceManager = new ResourceManager();
	}
	return *resourceManager;
}

void ResourceManager::destroyResourceManager()
{
	if (resourceManager != nullptr)
		delete resourceManager;
}

Camera * ResourceManager::getCamera()
{
	return camera;
}

void ResourceManager::setCamera(Camera* camera)
{
	this->camera = camera;
}

void ResourceManager::setProjectileObject(Object * object)
{
	projectileObject = object;
}

Object * ResourceManager::getProjectileObject()
{
	return projectileObject;
}

void ResourceManager::setProjectileShader(ShaderInterface * shader)
{
	projectileShader = shader;
}

ShaderInterface* ResourceManager::getProjectileShader()
{
	return  projectileShader;
}

void ResourceManager::removeEntity(Entity * entity)
{
	EntityArray->erase(std::remove_if(EntityArray->begin(), EntityArray->end(), [entity](auto it) {return it == entity; }), EntityArray->end());
	delete entity;
}

