#pragma once
#include <iostream>
#include "Dependencies\glew\glew.h"
#include "Dependencies\glfw\glfw3.h"
#include "RenderSystem.h"
#include "ResourceManager.h"

class GameManager
{
	static GameManager *gameManager;

	ResourceManager *resourceManager;
	GLFWwindow* _window;
	bool _running;
	RenderSystem *_renderSystem;
	float aspect = 1;

	static void GameManager::windowResize(GLFWwindow* window, int width, int height);

	GameManager(bool running, GLFWwindow* window, RenderSystem *renderSystem, ResourceManager* resourceManager);
	~GameManager();
public:
	static GameManager& getGameManager();
	static void destroyGameManager();
	void runGameLoop();
};