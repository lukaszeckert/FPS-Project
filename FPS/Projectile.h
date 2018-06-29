#pragma once
#include "Models/Entity.h"
#include "LightSystem/PointLight.h"
#include "LightSystem/LightSystem.h"
#include "Managers/ResourceManager.h"

class Projectile
{

public:
	Entity* entity;
	PointLight* pointLight;
	glm::vec3 direction, color;
	float speed;
	float time = 0;
	Projectile(Entity* entity, PointLight* pointLight);
	~Projectile();
};

