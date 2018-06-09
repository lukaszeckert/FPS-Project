#pragma once
#include "../Dependencies/glm/glm.hpp"
class SpotLight
{
public:
	glm::vec3 position;
	glm::vec3 direction;
	
	float cutOff = glm::radians(12.5f);
	float outerCutOff = glm::radians(17.5);

	float constant = 1.0;
	float linear = 0.7;
	float quadratic = 1.8;
	
	glm::vec3 ambient = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 diffuse = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 specular = glm::vec3(1.0, 1.0, 1.0);
	SpotLight();
	~SpotLight();
};

