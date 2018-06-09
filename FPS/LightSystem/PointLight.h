#pragma once
#include "../Dependencies/glm/glm.hpp"
struct PointLight {

public:
	bool active = false;
	glm::vec3 position;
	
	float constant = 1.0f;
	float linear = 1.0f;
	float quadratic = 1.8f;
	
	glm::vec3 ambient = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 diffuse = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 specular = glm::vec3(1.0, 1.0, 1.0);
	PointLight();
	PointLight(glm::vec3 postion, float constant = 1.0f, float linear = 1.0, float quadratic = 1.8, glm::vec3 ambient = glm::vec3(1.0, 1.0, 1.0), glm::vec3 diffuse = glm::vec3(1.0, 1.0, 1.0), glm::vec3 specular = glm::vec3(1.0, 1.0, 1.0));
	~PointLight();
};