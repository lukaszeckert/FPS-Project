#include "ResourceManager.h"

void tickCallback(btDynamicsWorld *world, btScalar timeStep) {
	int numManifolds = world->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++)
	{
			btPersistentManifold* contactManifold =  world->getDispatcher()->getManifoldByIndexInternal(i);
			const btCollisionObject* obA = contactManifold->getBody0();
			const btCollisionObject* obB = contactManifold->getBody1();

			int numContacts = contactManifold->getNumContacts();
			for (int j = 0; j < numContacts; j++)
			{
					btManifoldPoint& pt = contactManifold->getContactPoint(j);
					if (pt.getDistance() < 0.f && obA != ResourceManager::getResourceManager().groundRigidBody
						&& obB != ResourceManager::getResourceManager().groundRigidBody)
					{
							std::cout << "Contact" << std::endl;
					}
			}
	}
}


ResourceManager *ResourceManager::resourceManager = nullptr;
ResourceManager::ResourceManager()
{
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();;
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -10, 0));
	dynamicsWorld->setInternalTickCallback(tickCallback);

	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo
					groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);


	shaderArray = new std::vector<ShaderInterface*>();
	//vertexBufferArray = new std::vector<VertexBuffer*>();
	EntityArray = new std::vector<Entity*>();
	TextureArray = new std::vector<Texture*>();
	ObjectArray = new std::vector<Object*>();
	lightSystem = LightSystem::getLightSystem();
	/*auto light = lightSystem->createPointLighs(glm::vec3(4, 0, 5));
	light->active = true;
	light->linear = 0.7;
	light->quadratic = 0.2;
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
	*/
}


ResourceManager::~ResourceManager()
{
	for (auto it = shaderArray->begin(); it != shaderArray->end(); ++it)
		delete (*it);
//	for (auto it = vertexBufferArray->begin(); it != vertexBufferArray->end(); ++it)
//		delete (*it);
	for (auto it = EntityArray->begin(); it != EntityArray->end(); ++it)
		delete (*it);

	for(auto it = ObjectArray->begin(); it != ObjectArray->end(); ++it)
		delete (*it);
	delete shaderArray;
//	delete  vertexBufferArray;
	delete EntityArray;
	delete ObjectArray;

	LightSystem::destroyLightSystem();

}

std::vector<ShaderInterface*>* ResourceManager::getShaderArray()
{
	return shaderArray;
}

/*std::vector<VertexBuffer*>* ResourceManager::getBufferArray()
{
	return vertexBufferArray;
}*/
std::vector<Entity *>* ResourceManager::getEntityArray()
{
	return EntityArray;
}
std::vector<Texture*>* ResourceManager::getTextureArray()
{
	return TextureArray;
}
std::vector<Object*>* ResourceManager::getObjectArray()
{
	return ObjectArray;
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
	return camera;
}

void ResourceManager::setCamera(Camera* camera)
{
	this->camera = camera;
}

