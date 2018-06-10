#pragma once
#include "../Managers/ResourceManager.h"

class Scane
{
	ShaderInterface* shader;
	ShaderInterface* shader_color;
	ResourceManager* resourceManager;
	void createShaders();
	void createLights();
	void createObjects();
	void createCamera();

public:
	Scane();
	//~Scane();
	void createScane();
};

