#pragma once
#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Models/VertexBuffer.h"
#include "../Models/Entity.h"

#include "../Interfaces/ShaderInterface.h"
#include "../LightSystem/LightSystem.h"
#include "../Models/Camera.h"
#include <vector>
#include <string>



class RenderSystem
{
	static RenderSystem* renderSystem;
	GLFWwindow *_window;
	
	RenderSystem(GLFWwindow *window);
	~RenderSystem();

public:
	static RenderSystem& getRenderSystem(GLFWwindow *window);
	static void destroyRenderSystem();
	void render(Mesh* mesh, glm::mat4x4 P, glm::mat4x4 V, glm::mat4x4 M, ShaderInterface *shader, glm::vec3 Cameraposition, glm::vec3 color, glm::vec3 position);
	void renderAll(std::vector<Entity*>* Entitys, Camera *camera,float aspect);
};