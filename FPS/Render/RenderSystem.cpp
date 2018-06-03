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

	glm::vec3 lightColor;
	lightColor.x = sin(glfwGetTime() * 2.0f);
	lightColor.y = sin(glfwGetTime() * 0.7f);
	lightColor.z = sin(glfwGetTime() * 1.3f);
	//std::cout << lightColor.x << "\n";
	Entitys->at(1)->color = lightColor;
	auto P = glm::perspective(50 * 3.14f / 180, aspect, 1.0f, 50.0f);
	auto V = glm::lookAt(camera->position, camera->dir, camera->up);
	
	for (int i = 0; i < Entitys->size(); ++i) {
		auto it = Entitys->at(i);
		auto M = translate(glm::mat4(1.0f), it->position);
		render(it, P, V, M, it->shaderInterface,camera->position);
		
	}
	glfwSwapBuffers(glfwGetCurrentContext());
}
void RenderSystem::render(Entity *entity, glm::mat4x4 P, glm::mat4x4 V, glm::mat4x4 M, ShaderInterface *shader, glm::vec3 cameraPosition)
{
	auto lighSystem = LightSystem::getLightSystem();


	glUseProgram(shader->getShader());
	
	glUniform4f(shader->getColor(), 1.0f, 1.0f, 0.0f, 1.0f);
	
	glUniformMatrix4fv(shader->getP(), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shader->getV(), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(shader->getM(), 1, false, glm::value_ptr(M));


	glm::vec3 lightColor;
	lightColor.x = sin(glfwGetTime() * 2.0f);
	lightColor.y = sin(glfwGetTime() * 0.7f);
	lightColor.z = sin(glfwGetTime() * 1.3f);

	shader->setVec3("objectColor", entity->color);
	shader->setVec3("lightColor", lighSystem->globalColor);

	shader->setVec3("lightPos", lighSystem->globalPosition);
	shader->setVec3("viewPos", cameraPosition);

	//materials

	glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.5f); // low influence
	shader->setVec3("material.ambient", 1.0, 0.5f, 0.31);
	shader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	shader->setVec3("material.specular", 1.0f, 0.5f, 0.31f);
	shader->setFloat("material.shininess", 128.0f);

	//light
	shader->setVec3("light.ambient",ambientColor);
	shader->setVec3("light.diffuse", diffuseColor);
	shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	//Texture
	shader->setInt("materialTex.diffuse", 0);
	shader->setVec3("materialTex.specular", 1.0f, 0.5f, 0.31f);
	shader->setFloat("materialTex.shininess", 32.0f);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, entity->diffuseMap);

	entity->vertexBuffer->configureVertexAttributes(shader);
	entity->vertexBuffer->renderVertexBuffer();

}