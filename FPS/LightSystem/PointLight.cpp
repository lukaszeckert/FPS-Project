#include "PointLight.h"


PointLight::PointLight()
{
}

PointLight::PointLight(glm::vec3 postion, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
	position(postion), constant(constant), linear(linear), quadratic(quadratic), ambient(ambient), diffuse(diffuse), specular(specular)
{
	entity = nullptr;
}

PointLight::~PointLight()
{
}

void PointLight::update()
{
	if (entity != nullptr)
		position = entity->position;
}

void PointLight::bind(Entity* entity)
{
	this->entity = entity;
}

void PointLight::unbind()
{
	entity = nullptr;
}
