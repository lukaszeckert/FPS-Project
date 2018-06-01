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
	globalPosition = glm::vec3(0);
	globalColor = glm::vec3(1);
	pointLights = new std::vector<PointLight*>();
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

PointLight * LightSystem::createPointLighs(glm::vec3 postion, glm::vec3 color)
{
	return new PointLight(postion, color);
}

void LightSystem::addPointLight(PointLight * pointLight)
{
	pointLights->push_back(pointLight);
}

void LightSystem::addPointLight(glm::vec3 position, glm::vec3 color)
{
	addPointLight(createPointLighs(position, color));
}

