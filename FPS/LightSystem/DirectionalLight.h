#pragma once
#include "../Dependencies/glm/glm.hpp"

struct DirectionalLight{
	glm::vec3 direction = glm::vec3(0, -1.0, 0.0);
	glm::vec3 ambient = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 diffuse = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 specular = glm::vec3(1.0, 1.0, 1.0);
	DirectionalLight();


};