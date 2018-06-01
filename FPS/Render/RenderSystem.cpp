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

		glMatrixMode(GL_PROJECTION);
		gluPerspective(75.0f, 1280.0 / 720.0f, 1, 1000);
		glViewport(0.0f, 0.0f, 1280.0f, 720.0f);
		glMatrixMode(GL_MODELVIEW);


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
void RenderSystem::renderAll(std::vector<Entity*>* Entitys, glm::vec3 eye, glm::vec3 center, glm::vec3 up, float aspect)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	auto P = glm::perspective(50 * 3.14f / 180, aspect, 1.0f, 50.0f);
	auto V = glm::lookAt(eye, center, up);
	
	for (int i = 0; i < Entitys->size(); ++i) {
		auto it = Entitys->at(i);
		auto M = translate(glm::mat4(1.0f), it->position);
		render(it->vertexBuffer, P, V, M, it->shaderInterface);
		
	}
	glfwSwapBuffers(glfwGetCurrentContext());
}
void RenderSystem::render(VertexBuffer *vertexBuffer, glm::mat4x4 P, glm::mat4x4 V, glm::mat4x4 M, ShaderInterface *shader)
{
	
	glUseProgram(shader->getShader());
	
	glUniform4f(shader->getColor(), 1.0f, 1.0f, 0.0f, 1.0f);
	
	glUniformMatrix4fv(shader->getP(), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shader->getV(), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(shader->getM(), 1, false, glm::value_ptr(M));

	vertexBuffer->configureVertexAttributes(shader);
	vertexBuffer->renderVertexBuffer();

}