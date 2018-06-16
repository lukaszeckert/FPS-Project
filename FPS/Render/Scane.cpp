#include "Scane.h"

void Scane::createShaders()
{
	shader = new ShaderInterface("Shaders/vMultiLight.glsl", "Shaders/fMultiLight.glsl");
	shader_color = new ShaderInterface("Shaders/vShader.glsl", "Shaders/fColor.glsl");
	auto shaderArray = resourceManager->getShaderArray();
	shaderArray->push_back(shader);
	shaderArray->push_back(shader_color);
}
 
void Scane::createLights()
{
	auto lightSystem = LightSystem::getLightSystem();
	auto light = lightSystem->createPointLighs(glm::vec3(4, 0, 5));
	light->active = true;
	light->linear = 0.7;
	light->quadratic = 0.2;
	lightSystem->addPointLight(light);

}

void Scane::createObjects()
{
	
	auto object = ObjectLoaderInterface::loadObjFile("GraphicModels/cube.obj", resourceManager->getTextureArray());
	float poz = 0;
	for (int i = 0; i < 4; ++i)
	{
		Entity* entity = new Entity(glm::vec3(0, 0, (i - 2) * 5), object, shader, glm::vec3(0.0, 1.0, 0.5));
		// entity->scale = glm::vec3(1.0f / (i + 1), 1.0f / (i + 1), 1.0f / (i + 1));
		resourceManager->getEntityArray()->push_back(entity);

	}
	Entity* entity = new Entity(glm::vec3(4, 0, 10), object, shader_color);
	// entity->scale = glm::vec3(0.1, 0.1, 0.1);
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
void Scane::createCamera()
{
	auto camera = new Camera();
	camera->position.x = -3;
	resourceManager->setCamera(camera);


}



Scane::Scane()
{
	resourceManager = &ResourceManager::getResourceManager();
}

void Scane::createScane()
{
	createShaders();
	createObjects();
	createLights();
	createCamera();
}
