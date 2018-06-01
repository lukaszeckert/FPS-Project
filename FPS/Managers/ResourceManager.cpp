#include "ResourceManager.h"



ResourceManager *ResourceManager::resourceManager = nullptr;
ResourceManager::ResourceManager()
{
	shaderArray = new std::vector<ShaderInterface*>();
	vertexBufferArray = new std::vector<VertexBuffer*>();
	EntityArray = new std::vector<Entity*>();
	TextureArray = new std::vector<Texture*>();

	lightSystem = LightSystem::getLightSystem();
	lightSystem->globalColor = glm::vec3(1.0, 1.0, 0);
	lightSystem->globalPosition = glm::vec3(5, 0, 7);

	ShaderInterface *shader = new ShaderInterface("Shaders\\vPhongTex.glsl", "Shaders\\fPhongTex.glsl");
	shaderArray->push_back(shader);
	camera = Camera();
	Texture *tex = new Texture("GraphicModels\\container2.png");
	TextureArray->push_back(tex);

	auto meshes = ObjectLoaderInterface::loadObjFile("GraphicModels\\cube.obj");
	float poz = 0;
	for (auto it : meshes)
	{
		
		auto vertexBuffer = new VertexBuffer(it.second.data(), sizeof(VertexData)*it.second.size(), GL_TRIANGLES, it.second.size(), sizeof(VertexData));
		vertexBufferArray->push_back(vertexBuffer);
		Entity *entity = new Entity(glm::vec3(0, 0, 5), vertexBuffer, shader,glm::vec3(0.0,1.0,0.5));
		EntityArray->push_back(entity);
		entity->diffuseMap = tex->getTexture();
	
		
	}
	//auto vertexBuffer = new VertexBuffer(meshes[0].second.data(), sizeof(VertexData)*meshes[0].second.size(), GL_TRIANGLES, meshes[0].second.size(), sizeof(GLfloat) * 8);
	shader = new ShaderInterface("Shaders\\vShader.glsl", "Shaders\\fWhite.glsl");
	shaderArray->push_back(shader);
	Entity *entity = new Entity(glm::vec3(5, 0, 7), vertexBufferArray->at(0), shader);
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

