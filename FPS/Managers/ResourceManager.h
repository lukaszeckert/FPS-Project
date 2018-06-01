#pragma once
#include <vector>
#include "..\Interfaces\ShaderInterface.h"
#include "..\Interfaces\ObjectLoaderInterface.h"
#include "..\Models\VertexBuffer.h"
#include "..\Models\Entity.h"


class ResourceManager
{
	std::vector<ShaderInterface *> *shaderArray;
	std::vector<VertexBuffer *> *vertexBufferArray;
	std::vector<Entity *> *EntityArray;
	static ResourceManager* resourceManager;
	ResourceManager();
	~ResourceManager();
public:
	std::vector<ShaderInterface *>* getShaderArray();
	std::vector<VertexBuffer *>* getBufferArray();
	std::vector<Entity*>* getEntityArray();
	static ResourceManager& getResourceManager();
	static void destroyResourceManager();
};

