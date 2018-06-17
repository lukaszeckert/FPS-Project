#pragma once
#include <glm/glm.hpp>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>


enum SCANE_OBJECT
{
	OBJECT = 0,
	LAYER = 1,
	PLAYER = 2,
	ENEMY =3
};
struct ObjectData {
	int id;

	glm::vec3 position;
	std::string filename;

};
struct LayerData {
	int id;

	glm::vec3 position;
	std::string filename;

};
struct EntityData {
	int id;
	int obj_id;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
};
struct Data{
	std::vector<ObjectData> objectData;
	std::vector<EntityData> entityData;
	std::vector<LayerData> layerData;

};
struct Layer {
	std::vector<std::vector<int>> objects;
	glm::vec3 offset;
};
class ScaneLoader
{
	ScaneLoader();
	~ScaneLoader();

public:
	static Data loadScane(std::string filename);
	static Layer loadLayer(std::string filename);
};

