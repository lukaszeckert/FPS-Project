#include "ResourceManager.h"



ResourceManager *ResourceManager::resourceManager = nullptr;
ResourceManager::ResourceManager()
{
	shaderArray = new std::vector<ShaderInterface*>();
	vertexBufferArray = new std::vector<VertexBuffer*>();
	EntityArray = new std::vector<Entity*>();
	TextureArray = new std::vector<Texture*>();

	lightSystem = LightSystem::getLightSystem();
	auto light = lightSystem->createPointLighs(glm::vec3(4, 0, 5));
	light->active = true;
	light->linear = 0.07;
	light->quadratic = 0.002;
	lightSystem->addPointLight(light);

	ShaderInterface *shader = new ShaderInterface("Shaders/vMultiLight.glsl", "Shaders/fMultiLight.glsl");
	shaderArray->push_back(shader);
	camera = Camera();
	camera.position.x = -3;
	

	auto meshes = ObjectLoaderInterface::loadObjFile("GraphicModels/cube.obj", TextureArray);
	float poz = 0;
	for(int i=0;i<4;++i)
	for (auto it : meshes->meshes)
	{
		auto vertexBuffer = new VertexBuffer(it->points.data(), sizeof(VertexData)*it->points.size(), GL_TRIANGLES, it->points.size(), sizeof(VertexData));
		vertexBufferArray->push_back(vertexBuffer);
		Entity *entity = new Entity(glm::vec3(0, 0, (i-2)*5), vertexBuffer, shader,glm::vec3(0.0,1.0,0.5));
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

}


ResourceManager::~ResourceManager()
{
	for (auto it = shaderArray->begin(); it != shaderArray->end(); ++it)
		delete (*it);
	for (auto it = vertexBufferArray->begin(); it != vertexBufferArray->end(); ++it)
		delete (*it);
	for (auto it = EntityArray->begin(); it != EntityArray->end(); ++it)
		delete (*it);

	delete shaderArray;
	delete  vertexBufferArray;
	delete EntityArray;
}

std::vector<ShaderInterface*>* ResourceManager::getShaderArray()
{
	return shaderArray;
}

std::vector<VertexBuffer*>* ResourceManager::getBufferArray()
{
	return vertexBufferArray;
}
std::vector<Entity *>* ResourceManager::getEntityArray()
{
	return EntityArray;
}
ResourceManager & ResourceManager::getResourceManager()
{
	if (resourceManager == nullptr)
	{
		resourceManager = new ResourceManager();
	}
	return *resourceManager;
}

void ResourceManager::destroyResourceManager()
{
	if (resourceManager != nullptr)
		delete resourceManager;
}

Camera * ResourceManager::getCamera()
{
	return &camera;
}

