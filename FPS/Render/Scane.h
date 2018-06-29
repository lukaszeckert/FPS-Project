#pragma once
#include "../Managers/ResourceManager.h"
#include "../Loaders/ScaneLoader.h"
#include <map>
#include <vector>
#include "../EnemyManager.h"

class Scane
{
	ShaderInterface* shader;
//	ShaderInterface* shader_color;
	ResourceManager* resourceManager;
	Object* enemyObject;
	std::map<int, Object*> object_map;
	void createShaders();
	void createLights();
	void createObjects(std::vector<ObjectData> objects);
	void createLayers(std::vector<LayerData> layers, std::vector<EntityData> entities);
	void createCamera();
	void createEnemies();

public:
	Scane();
	//~Scane();
	void createScane();
};

