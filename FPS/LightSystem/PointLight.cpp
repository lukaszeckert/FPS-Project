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
	if (entity != nullptr) {
		auto pos = entity->rigidBody->getWorldTransform().getOrigin();
		position = glm::vec3(pos.x(), pos.y(), pos.z());
	}
}

void PointLight::bind(Entity* entity)
{
	this->entity = entity;
}

void PointLight::unbind()
{
	entity = nullptr;
}
