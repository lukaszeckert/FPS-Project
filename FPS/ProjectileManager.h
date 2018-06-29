#pragma once
#include "Projectile.h"
#include <vector>
#include <algorithm>
#include "Managers/ResourceManager.h"

class ProjectileManager
{
	static ProjectileManager *projectileManager;
	std::vector<Projectile*>* projectiles;
	Object* object;
	ShaderInterface* shader;
	ProjectileManager();
	~ProjectileManager();
public:
	static ProjectileManager& getProjectileManager();
	static void destroyProjectileManager();
	Projectile* createProjectile(glm::vec3 position, glm::vec3 direction, float speed, glm::vec3 color);
	void destoryProjectile(Projectile* projectile);
	void update(float dTime);
};

