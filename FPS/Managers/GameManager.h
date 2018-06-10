#pragma once
#include <iostream> 
#include <GL/glew.h>
#include <glfw/glfw3.h>
#include "../Render/RenderSystem.h"
#include "../Managers/ResourceManager.h"
#include <functional>

class GameManager
{
	static GameManager *gameManager;

	ResourceManager *resourceManager;
	GLFWwindow* _window;
	bool _running;
	RenderSystem *_renderSystem;
	float aspect = 1;

	static void windowResize(GLFWwindow* window, int width, int height);
	static void wrapperMouseClick(GLFWwindow* window, double xpos, double ypos);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void processInput(GLFWwindow *windows, float dTime);

	GameManager(bool running, GLFWwindow* window, RenderSystem *renderSystem, ResourceManager* resourceManager);
	~GameManager();
public:
	static GameManager& getGameManager();
	static void destroyGameManager();
	void runGameLoop();
};