#include "PointLight.h"


PointLight::PointLight()
{
}

PointLight::PointLight(glm::vec3 postion, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
	position(postion), constant(constant), linear(linear), quadratic(quadratic), ambient(ambient), diffuse(diffuse), specular(specular)
{
}

PointLight::~PointLight()
{
}
