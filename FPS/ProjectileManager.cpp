#include "ProjectileManager.h"
ProjectileManager* ProjectileManager::projectileManager = nullptr;
ProjectileManager::~ProjectileManager()
{
	for (auto it : *projectiles)
		delete it;
	delete projectiles;
}
ProjectileManager::ProjectileManager()
{
	projectiles = new std::vector<Projectile*>();
	object = nullptr;
	shader = nullptr;
}

ProjectileManager& ProjectileManager::getProjectileManager()
{
	if (projectileManager->projectileManager == nullptr)
		projectileManager = new ProjectileManager();
	return *projectileManager;
}

void ProjectileManager::destroyProjectileManager()
{
	delete projectileManager;
}

Projectile * ProjectileManager::createProjectile(glm::vec3 position, glm::vec3 direction, float speed, glm::vec3 color)
{
	if (object == nullptr)
	{
		object = (&ResourceManager::getResourceManager())->getProjectileObject();
		shader = (&ResourceManager::getResourceManager())->getProjectileShader();
	}
	
	auto entity = new Entity(position+normalize(direction)*2.0f, object, shader);
	entity->color = color;
	
	
	auto light = LightSystem::getLightSystem()->bind(entity);
	light->diffuse = color;
	light->ambient = color;
	light->specular = color;
	light->constant = 1;
	light->linear = 0.7;
	light->quadratic = 0.07;
	
	auto res = new Projectile(entity, light);
	projectiles->push_back(res);

	res->direction = direction;
	res->speed = speed;
	auto velocity = glm::normalize(direction)*speed;
	entity->rigidBody->activate(true);
	entity->rigidBody->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));

	(&ResourceManager::getResourceManager())->getEntityArray()->push_back(entity);
	return res;
}

void ProjectileManager::destoryProjectile(Projectile * projectile)
{
	projectiles->erase(std::remove(projectiles->begin(), projectiles->end(), projectile), projectiles->end());
	delete projectile;
}

void ProjectileManager::update()
{
	for (auto it : *projectiles) {
		glm::vec3 velocity = glm::normalize(it->direction)*it->speed;
		it->entity->rigidBody->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
	}
}
