#pragma once
#include "../Dependencies/glm/glm.hpp"
class PointLight {
	glm::vec3 position;
	glm::vec3 color;
public:
	PointLight(glm::vec3 postion, glm::vec3 color);
	~PointLight();
};