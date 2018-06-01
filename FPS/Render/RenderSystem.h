#pragma once
#define GLFW_INCLUDE_GLU
#include "..\Dependencies\glew\glew.h"
#include "..\Dependencies\glfw\glfw3.h"
#include "..\Dependencies\glm\glm.hpp"
#include "..\Dependencies\glm\gtc\type_ptr.hpp"
#include "..\Dependencies\glm\gtc\matrix_transform.hpp"

#include "..\Models\VertexBuffer.h"
#include "..\Models\Entity.h"

#include "..\Interfaces\ShaderInterface.h"

#include <vector>


class RenderSystem
{
	static RenderSystem* renderSystem;
	GLFWwindow *_window;
	
	RenderSystem(GLFWwindow *window);
	~RenderSystem();

public:
	static RenderSystem& getRenderSystem(GLFWwindow *window);
	static void destroyRenderSystem();
	void render(VertexBuffer *vertexBuffer, glm::mat4x4 P, glm::mat4x4 V, glm::mat4x4 M, ShaderInterface *shader );
	void renderAll(std::vector<Entity*>* Entitys, glm::vec3 eye, glm::vec3 center, glm::vec3 up, float aspect);
};