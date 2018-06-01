#pragma once
#include "../Dependencies/glm/glm.hpp"
struct PointLight {
	glm::vec3 position;
	glm::vec3 color;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
public:
	PointLight();
	PointLight::PointLight(glm::vec3 postion, glm::vec3 color);
	~PointLight();
};