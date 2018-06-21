#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#include "ScaneLoader.h"


ScaneLoader::ScaneLoader()
{
}


ScaneLoader::~ScaneLoader()
{
}

Data ScaneLoader::loadScane(std::string filename)
{
	Data res;
	
	std::ifstream infile(filename);
	std::string line;
	while (std::getline(infile, line))
	{
		Data *data = new Data;
		//Data *data = new Data();
		std::stringstream iss(line);
		char c;
		std::string map_name;
		iss >> c;
		std::string s;
		if (c == 'o') {
			ObjectData data;
			iss >> data.id;
			iss >> data.position.x >> data.position.y >> data.position.z;
			iss >> data.filename;
			res.objectData.push_back(data);
		}
		if (c == 'l') {
			LayerData data;
			iss >> data.id;
			iss >> data.position.x >> data.position.y >> data.position.z;
			iss >> data.filename;
			res.layerData.push_back(data);
		}
		if (c == 'e') {
			EntityData data;
			iss >> data.id;
			iss >> data.position.x >> data.position.y >> data.position.z;
			iss >> data.scale.x >> data.scale.y >> data.scale.z;
			iss >> data.rotation.x >> data.rotation.y >> data.rotation.z;
			iss >> data.obj_id;
			//std::cout << "e:" << data.position.x <<  " " <<  data.position.y <<" " << data.position.z << "\n";
			res.entityData.push_back(data);

		}
			
		
		
	}
	return res;
}

Layer ScaneLoader::loadLayer(std::string filename)
{
	Layer res;
	std::ifstream infile;
	try {
		infile.open(filename);
	}
	catch (std::ios_base::failure& e) {
		std::cerr << e.what() << '\n';
	}
	std::string line;
	char c;
	int n,m;
	
	for (int i = 0; i < 2; ++i) {
		infile >> c;
		if (c == 'x')
			infile >> res.offset.x;
		if (c == 'y')
			infile >> res.offset.y;
		if (c == 'z')
			infile >> res.offset.z;
	}
	infile >> n >> m;
	res.objects.resize(n);
	for (int i = 0; i < n; ++i) {
		res.objects[i].resize(m);
		for (int j = 0; j < m; ++j)
		{
			infile >> res.objects[i][j];
		}
	}

	return res;
}
