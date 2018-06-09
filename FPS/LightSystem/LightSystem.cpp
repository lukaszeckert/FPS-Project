#include "LightSystem.h"

LightSystem *LightSystem::lightsytem = nullptr;
LightSystem::~LightSystem()
{
	for (auto it : *pointLights)
		delete it;
	delete pointLights;
}
LightSystem::LightSystem()
{
	pointLights = new std::vector<PointLight*>();
	directionalLight = new DirectionalLight();
	spotLight = new SpotLight();
}
LightSystem * LightSystem::getLightSystem()
{
	if (lightsytem == nullptr)
	{
		lightsytem = new LightSystem();
	}
	return lightsytem;
}

void LightSystem::destroyLightSystem()
{
	if (lightsytem != nullptr)
		delete lightsytem;
}

std::vector<PointLight*>* LightSystem::getPointLights()
{
	return pointLights;
}

PointLight * LightSystem::createPointLighs(glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	return new PointLight(position, constant, linear, quadratic, ambient, diffuse, specular);
}

DirectionalLight * LightSystem::setDirectionalLightProperties(glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	directionalLight->direction = dir;
	directionalLight->ambient = ambient;
	directionalLight->diffuse = diffuse;
	directionalLight->specular = specular;
	return directionalLight;
}

SpotLight * LightSystem::setSpotLightProperties(glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	spotLight->position = position;
	spotLight->direction = direction;
	spotLight->cutOff = cutOff;
	spotLight->outerCutOff = outerCutOff;
	spotLight->constant = constant;
	spotLight->linear = linear;
	spotLight->quadratic = quadratic;
	spotLight->ambient = ambient;
	spotLight->diffuse = diffuse;
	spotLight->specular = specular;
	return spotLight;
}

DirectionalLight * LightSystem::getDirectionalLight()
{
	return directionalLight;
}

SpotLight * LightSystem::getSpotLight()
{
	return spotLight;
}

void LightSystem::addPointLight(PointLight * pointLight)
{
	pointLights->push_back(pointLight);
}

void LightSystem::addPointLight(glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	addPointLight(new PointLight(PointLight(position, constant, linear, quadratic, ambient, diffuse, specular)));
}



