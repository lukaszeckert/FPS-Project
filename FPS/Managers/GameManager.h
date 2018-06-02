#pragma once
#include <iostream> 
#include <glew/glew.h>
#include <glfw/glfw3.h>
#include "../Render/RenderSystem.h"
#include "../Managers/ResourceManager.h"


class GameManager
{
	static GameManager *gameManager;

	ResourceManager *resourceManager;
	GLFWwindow* _window;
	bool _running;
	RenderSystem *_renderSystem;
	float aspect = 1;

	static void windowResize(GLFWwindow* window, int width, int height);

	GameManager(bool running, GLFWwindow* window, RenderSystem *renderSystem, ResourceManager* resourceManager);
	~GameManager();
public:
	static GameManager& getGameManager();
	static void destroyGameManager();
	void runGameLoop();
};