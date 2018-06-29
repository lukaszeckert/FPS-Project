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
//	auto light = lightSystem->createPointLighs(glm::vec3(-4, 2, 5));


//	light = lightSystem->createPointLighs(glm::vec3(4, 2, 5));
//	light->active = true;
//	light->linear = 0.007;
//	light->quadratic = 0.0002;
//	light->diffuse = glm::vec3(1, 1, 1);
//	light->ambient = glm::vec3(1, 1, 1);
//	light->specular = glm::vec3(1, 1, 1);
//	lightSystem->addPointLight(light);

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
	enemyObject = ObjectLoaderInterface::loadObjFile("GraphicModels/nanoSmall.obj", resourceManager->getTextureArray());
	resourceManager->getObjectArray()->push_back(object);
/*	auto object = ObjectLoaderInterface::loadObjFile("GraphicModels/cube.obj", resourceManager->getTextureArray());
	float poz = 0;
	for (int i = 0; i < 4; ++i)
	{
		Entity* entity = new Entity(glm::vec3(0, 0, (i - 2) * 5), object, shader, glm::vec3(0.0, 1.0, 0.5));
		// entity->scale = glm::vec3(1.0f / (i + 1), 1.0f / (i + 1), 1.0f / (i + 1));
		resourceManager->getEntityArray()->push_back(entity);

	}
	Entity* entity = new Entity(glm::vec3(4, 15, 5), object, shader_color);
	entity->scale = glm::vec3(0.1, 0.1, 0.1);
	entity->color = glm::vec3(0, 1, 0);
	resourceManager->getEntityArray()->push_back(entity);

	entity = new Entity(glm::vec3(-4, 15, 5), object, shader_color);
	entity->scale = glm::vec3(0.1, 0.1, 0.1);
	entity->color = glm::vec3(1, 0, 0);
	resourceManager->getEntityArray()->push_back(entity);

//	object = ObjectLoaderInterface::loadObjFile("GraphicModels/nanosuit.obj", resourceManager->getTextureArray());

//	entity = new Entity(glm::vec3(0, 0, 10), object, shader);
//	entity->scale = glm::vec3(0.1, 0.1, 0.1);
//	resourceManager->getEntityArray()->push_back(entity);

	object = ObjectLoaderInterface::loadObjFile("GraphicModels/floor.obj", resourceManager->getTextureArray());
	entity = new Entity(glm::vec3(0, 0, 5), object, shader);
	//	entity->scale = glm::vec3(0.1, 0.1, 0.1);
	resourceManager->getEntityArray()->push_back(entity);
	entity = new Entity(glm::vec3(2, 0, 5), object, shader);
	//	entity->scale = glm::vec3(0.1, 0.1, 0.1);
	resourceManager->getEntityArray()->push_back(entity);

	/*		auto vertexBuffer = new VertexBuffer(it->points.data(), sizeof(VertexData)*it->points.size(), GL_TRIANGLES, it->points.size(), sizeof(VertexData));
			vertexBufferArray->push_back(vertexBuffer);
			Entity *entity = new Entity(glm::vec3(0, 0, (i - 2) * 5), vertexBuffer, shader, glm::vec3(0.0, 1.0, 0.5));
			entity->scale = glm::vec3(1.0f / (i + 1), 1.0f / (i + 1), 1.0f / (i + 1));
			EntityArray->push_back(entity);
			entity->diffuseMap = it->tex->getTexture();
			entity->specularMap = it->tex_spec->getTexture();
			}
			//auto vertexBuffer = new VertexBuffer(meshes[0].second.data(), sizeof(VertexData)*meshes[0].second.size(), GL_TRIANGLES, meshes[0].second.size(), sizeof(GLfloat) * 8);
			shader = new ShaderInterface("Shaders/vShader.glsl", "Shaders/fColor.glsl");
			shaderArray->push_back(shader);
			Entity *entity = new Entity(glm::vec3(4, 0, 10), vertexBufferArray->at(0), shader);
			entity->scale = glm::vec3(0.1, 0.1, 0.1);
			EntityArray->push_back(entity);
			*/
	
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

	
	//EnemyManager::getEnemyManager().createEnemy(glm::vec3(10, 2, 50), enemyObject, shader);

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
