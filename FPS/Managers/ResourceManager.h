#pragma once
#include <vector>
#include "../Interfaces/ShaderInterface.h"
#include "../Interfaces/ObjectLoaderInterface.h"
#include "../Models/VertexBuffer.h"
#include "../Models/Entity.h"
#include "../Models/Texture.h"
#include "../LightSystem/LightSystem.h"
#include "../Models/Camera.h"


class ResourceManager
{
	std::vector<ShaderInterface *> *shaderArray;
	//std::vector<VertexBuffer *> *vertexBufferArray;
	std::vector<Entity *> *EntityArray;
	std::vector<Texture *> *TextureArray;
	std::vector<Object *> *ObjectArray;
	LightSystem* lightSystem;
	Camera *camera;
	static ResourceManager* resourceManager;
	ResourceManager();
	~ResourceManager();
public:
	std::vector<ShaderInterface *>* getShaderArray();
//	std::vector<VertexBuffer *>* getBufferArray();
	std::vector<Entity*>* getEntityArray();
	std::vector<Texture *>* getTextureArray();
	std::vector<Object *>* getObjectArray();
	static ResourceManager& getResourceManager();
	static void destroyResourceManager();
	Camera* getCamera();
	void setCamera(Camera* camera);
};

