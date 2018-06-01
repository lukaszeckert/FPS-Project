#pragma once
#include <vector>
#include "PointLight.h"
#include "../Dependencies/glm/glm.hpp"
class LightSystem {
	
	static LightSystem* lightsytem;
	std::vector<PointLight*> *pointLights;

	LightSystem();
	~LightSystem();
public:
	glm::vec3 globalPosition;
	glm::vec3 globalColor;

	static LightSystem* getLightSystem();
	static void destroyLightSystem();
	std::vector<PointLight*>* getPointLights();
	PointLight* createPointLighs(glm::vec3 postion, glm::vec3 color);
	void addPointLight(PointLight* pointLight);
	void addPointLight(glm::vec3 postion, glm::vec3 color);
	

};