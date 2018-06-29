#pragma once

#include "Models/Entity.h"
#include "Managers/ResourceManager.h"
#include "ProjectileManager.h"

class Enemy
{
	Entity* entity;
	glm::vec3 front;
	float hp;
	float remainingReloadTime;
	float RELOAD_TIME = 3;
	void lookAt(glm::vec3 position);
	bool canShoot(glm::vec3 position);
public:
	Enemy(Entity* entity, float hp=100);
	~Enemy();
	void update(float dTime);
	float getHp();
	void damage(float dm);
};

