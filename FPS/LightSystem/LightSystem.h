#pragma once
#include <vector>
#include <algorithm>
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "../Dependencies/glm/glm.hpp"
class LightSystem {
	
	static LightSystem* lightsytem;
	std::vector<PointLight*> *pointLights;
	std::vector<PointLight*> *unbindedLights;
	DirectionalLight* directionalLight;
	SpotLight* spotLight;

	LightSystem();
	~LightSystem();
public:

	static LightSystem* getLightSystem();
	static void destroyLightSystem();
	std::vector<PointLight*>* getPointLights();
	PointLight* createPointLighs(glm::vec3 postion, float constant=1.0f, float linear=1.0, float quadratic=1.8, glm::vec3 ambient=glm::vec3(1.0,1.0,1.0), glm::vec3 diffuse = glm::vec3(1.0, 1.0, 1.0), glm::vec3 specular = glm::vec3(1.0, 1.0, 1.0));
	DirectionalLight* setDirectionalLightProperties(glm::vec3 dir = glm::vec3(0, -1.0, 0.0), glm::vec3 ambient = glm::vec3(1.0, 1.0, 1.0), glm::vec3 diffuse = glm::vec3(1.0, 1.0, 1.0), glm::vec3 specular = glm::vec3(1.0, 1.0, 1.0));
	SpotLight* setSpotLightProperties(glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff, float constant, float linear, float quadratic, glm::vec3 ambient = glm::vec3(1.0, 1.0, 1.0), glm::vec3 diffuse = glm::vec3(1.0, 1.0, 1.0), glm::vec3 specular = glm::vec3(1.0, 1.0, 1.0));
	DirectionalLight* getDirectionalLight();
	SpotLight* getSpotLight();
	void addPointLight(PointLight* pointLight);
	void addPointLight(glm::vec3 postion, float constant = 1.0f, float linear = 1.0, float quadratic = 1.8, glm::vec3 ambient = glm::vec3(1.0, 1.0, 1.0), glm::vec3 diffuse = glm::vec3(1.0, 1.0, 1.0), glm::vec3 specular = glm::vec3(1.0, 1.0, 1.0));
	void update();
	PointLight* bind(Entity* entity);
	PointLight* unbind(PointLight* light);
};