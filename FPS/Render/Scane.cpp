#include "Scane.h"


void Scane::createShaders()
{
	shader = new ShaderInterface("Shaders/vMultiLight.glsl", "Shaders/fMultiLight.glsl");
	//shader_color = new ShaderInterface("Shaders/vShader.glsl", "Shaders/fColor.glsl");
	auto shaderArray = resourceManager->getShaderArray();
	shaderArray->push_back(shader);
	auto shader_projectile = new ShaderInterface("Shaders/vShader.glsl", "Shaders/fColor.glsl");
	shaderArray->push_back(shader_projectile);
	resourceManager->setProjectileShader(shader_projectile);
		//shaderArray->push_back(shader_color);
}
 
void Scane::createLights()
{
	auto lightSystem = LightSystem::getLightSystem();
	lightSystem->getDirectionalLight()->ambient = glm::vec3(0.1, 0.1, 0.1);
	lightSystem->getDirectionalLight()->diffuse = glm::vec3(0.1, 0.1, 0.1);
	lightSystem->getDirectionalLight()->specular = glm::vec3(0.1, 0.1, 0.1);

}

void Scane::createObjects(std::vector<ObjectData> objects)
{
	for (auto ob : objects)
	{
		auto object = ObjectLoaderInterface::loadObjFile(ob.filename.c_str(), resourceManager->getTextureArray());
		resourceManager->getObjectArray()->push_back(object);
		object_map[ob.id] = object;
	}
	auto object = ObjectLoaderInterface::loadObjFile("GraphicModels/Projectile.obj", resourceManager->getTextureArray());
	resourceManager->getObjectArray()->push_back(object);
	resourceManager->setProjectileObject(object);
	enemyObject = ObjectLoaderInterface::loadObjFile("GraphicModels/corner3.obj", resourceManager->getTextureArray());
	resourceManager->getObjectArray()->push_back(object);
	
}
void Scane::createLayers(std::vector<LayerData> layers, std::vector<EntityData> entities)
{
	std::map<int, EntityData> entity_map;
	for (auto it : entities)
		entity_map[it.id] = it;
	for (auto la : layers)
	{
		
		auto layer = ScaneLoader::loadLayer(la.filename);
		glm::vec3 offset = layer.offset;
		for(int row=0;row<layer.objects.size(); ++row)
			for (int col=0;col<layer.objects[row].size();++col)
			{
				
				if (entity_map.find(layer.objects[row][col]) != entity_map.end()) {
					auto entityData = entity_map[layer.objects[row][col]];
					auto object = object_map[entityData.obj_id];
					glm::vec3 position = glm::vec3(la.position.x + row*offset.x, la.position.y, la.position.z + col*offset.z)+entityData.position;
					glm::vec3 scale = entityData.scale;
					glm::vec3 rotation = entityData.rotation;
					rotation = glm::vec3(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z));
					Entity* entity = new Entity(position, object, shader, EntityType::OTHER, rotation);
					entity->scale = scale;
				//	entity->rotation = rotation;
					resourceManager->getEntityArray()->push_back(entity);
				}
				
			}
	}
}
void Scane::createCamera()
{
	auto camera = new Camera();
	camera->position = glm::vec3(3, 3, 3);
	resourceManager->setCamera(camera);


}

void Scane::createEnemies()
{
	EnemyManager::getEnemyManager().createEnemy(glm::vec3(23, 1, 47), enemyObject, shader);
	EnemyManager::getEnemyManager().createEnemy(glm::vec3(11, 1, 9), enemyObject, shader);
	EnemyManager::getEnemyManager().createEnemy(glm::vec3(42, 1, 7), enemyObject, shader);
	EnemyManager::getEnemyManager().createEnemy(glm::vec3(74, 1, 11), enemyObject, shader);
	EnemyManager::getEnemyManager().createEnemy(glm::vec3(58, 1, 61), enemyObject, shader);
	EnemyManager::getEnemyManager().createEnemy(glm::vec3(40, 1, 90), enemyObject, shader);
}



Scane::Scane()
{
	resourceManager = &ResourceManager::getResourceManager();
}

void Scane::createScane()
{
	auto scane = ScaneLoader::loadScane("GraphicModels/Scane/big_scane.txt");
	
	createShaders();
	createObjects(scane.objectData);
	createLayers(scane.layerData, scane.entityData);
	createLights();
	createCamera();
	createEnemies();
	
}
