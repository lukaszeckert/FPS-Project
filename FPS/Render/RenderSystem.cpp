#include "RenderSystem.h"
#include <iostream>
RenderSystem *RenderSystem::renderSystem = nullptr;


RenderSystem::RenderSystem(GLFWwindow *window): _window(window){

}
RenderSystem::~RenderSystem(){

}

RenderSystem& RenderSystem::getRenderSystem(GLFWwindow *window)
{
	
	if (renderSystem == nullptr)
	{
		renderSystem = new RenderSystem(window);
	
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//glMatrixMode(GL_PROJECTION);
	//	gluPerspective(75.0f, 1280.0 / 720.0f, 1, 1000);

	}
	return *renderSystem;
}
void RenderSystem::destroyRenderSystem()
{
	if (renderSystem != nullptr)
	{
		delete renderSystem;
	}

}
void RenderSystem::renderAll(std::vector<Entity*>* Entitys,Camera* camera,float aspect)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	auto P = glm::perspective(50 * 3.14f / 180, aspect, 1.0f, 50.0f);
	auto V = glm::lookAt(camera->position, camera->position+camera->dir, camera->up);
	
	for (size_t i = 0; i < Entitys->size(); ++i) {
		auto it = Entitys->at(i);
		auto M = translate(glm::mat4(1.0f), it->position);

		M = glm::rotate(M, it->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		M = glm::rotate(M, it->rotation.z, glm::vec3(0.0f, 1.0f, 0.0f));
		M = glm::rotate(M, it->rotation.y, glm::vec3(0.0f, 0.0f, 1.0f));
		M = glm::scale(M, it->scale);
		for(auto mesh : it->object->meshes)
			render(mesh, P, V, M, it->shaderInterface,camera->position, it->color);
		
	}
	glfwSwapBuffers(glfwGetCurrentContext());
}
void RenderSystem::render(Mesh *mesh, glm::mat4x4 P, glm::mat4x4 V, glm::mat4x4 M, ShaderInterface *shader, glm::vec3 cameraPosition, glm::vec3 color)
{
	auto lighSystem = LightSystem::getLightSystem();


	glUseProgram(shader->getShader());
	
	glUniform4f(shader->getColor(), 1.0f, 1.0f, 0.0f, 1.0f);
	
	glUniformMatrix4fv(shader->getP(), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shader->getV(), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(shader->getM(), 1, false, glm::value_ptr(M));



	shader->setVec3("objectColor", color);
	shader->setVec3("viewPos", cameraPosition);

	//materials
	//TODO add material information to entity class 
//	shader->setVec3("material.ambient", 1.0, 0.5f, 0.31);
//	shader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
//	shader->setVec3("material.specular", 1.0f, 0.5f, 0.31f);
//	shader->setFloat("material.shininess", 128.0f);

	//light
	int pointLightsNumber = 0;
	for (auto it : *lighSystem->getPointLights()) {
		if (it->active == true)
		{
			
			shader->setVec3("pointLights["+std::to_string(pointLightsNumber)+"].position", it->position);
			shader->setVec3("pointLights["+std::to_string(pointLightsNumber)+"].ambient", it->ambient);
			shader->setVec3("pointLights[" + std::to_string(pointLightsNumber) + "].diffuse", it->diffuse);
			shader->setVec3("pointLights[" + std::to_string(pointLightsNumber) + "].specular", it->specular);

			shader->setFloat("pointLights[" + std::to_string(pointLightsNumber) + "].constant", it->constant);
			shader->setFloat("pointLights[" + std::to_string(pointLightsNumber) + "].linear", it->linear);
			shader->setFloat("pointLights[" + std::to_string(pointLightsNumber) + "].quadratic", it->quadratic);
			pointLightsNumber++;
		}
	}

	shader->setInt("point_lights_number", pointLightsNumber);

	auto dirLight = lighSystem->getDirectionalLight();
	shader->setVec3("dirLight.direction", dirLight->direction);
	shader->setVec3("dirLight.ambient", dirLight->ambient);
	shader->setVec3("dirLight.diffuse", dirLight->diffuse);
	shader->setVec3("dirLight.specular", dirLight->specular);

	auto spotLight = lighSystem->getSpotLight();
	shader->setVec3("spotLight.position", spotLight->position);
	shader->setVec3("spotLight.direction", spotLight->direction);
	
	shader->setFloat("spotLight.cutOff", spotLight->cutOff);
	shader->setFloat("spotLight.outerCutOff", spotLight->outerCutOff);
	shader->setFloat("spotLight.constant", spotLight->constant);
	shader->setFloat("spotLight.linear", spotLight->linear); 
	shader->setFloat("spotLight.quadratic", spotLight->quadratic);

	shader->setVec3("spotLight.ambient", spotLight->ambient);
	shader->setVec3("spotLight.diffuse", spotLight->diffuse);
	shader->setVec3("spotLight.specular", spotLight->specular);



	//Texture
	shader->setInt("materialTex.diffuse", 0);
	shader->setInt("materialTex.specular", 1);
	shader->setFloat("materialTex.shininess", 1.0f);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->tex->getTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mesh->tex_spec->getTexture());

	mesh->vertexBuffer->configureVertexAttributes(shader); //TODO change to configureVertexAttributes()
	mesh->vertexBuffer->renderVertexBuffer();

}