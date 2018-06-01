#include "ResourceManager.h"
#include "TriangleV.h"


ResourceManager *ResourceManager::resourceManager = nullptr;
ResourceManager::ResourceManager()
{
	shaderArray = new std::vector<ShaderInterface*>();
	ShaderInterface *shader = new ShaderInterface("vShader.glsl", "fShader.glsl");
	shaderArray->push_back(shader);
	
	vertexBufferArray = new std::vector<VertexBuffer*>();
//	VertexBuffer *vertexBuffer = new VertexBuffer(vertices2, sizeof(vertices2), GL_TRIANGLES, sizeof(vertices2)/ sizeof(GLfloat), sizeof(GLfloat) * 3);
//	vertexBufferArray->push_back(vertexBuffer);

	EntityArray = new std::vector<Entity*>();
//	Entity *entity = new Entity(glm::vec3(0,-3,5),vertexBuffer, shader);
	//EntityArray->push_back(entity);
//	entity = new Entity(glm::vec3(-1, 0, 5), vertexBuffer, shader);
	//EntityArray->push_back(entity);
	auto meshes = ObjectLoaderInterface::loadObjFile("box_stack.obj");
	float poz = 0;
	for (auto it : meshes)
	{
		
		auto vertexBuffer = new VertexBuffer(it.second.data(), sizeof(VertexData)*it.second.size(), GL_TRIANGLES, it.second.size(), sizeof(GLfloat) * 8);
		vertexBufferArray->push_back(vertexBuffer);
		Entity *entity = new Entity(glm::vec3(poz, 0, 5), vertexBuffer, shader);
		EntityArray->push_back(entity);
		//poz += 2;
		
	}

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

