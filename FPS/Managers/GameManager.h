#pragma once
#include <iostream> 
#include <GL/glew.h>
#include <glfw/glfw3.h>
#include "../Render/RenderSystem.h"
#include "../Managers/ResourceManager.h"
#include "../Render/Scane.h"
#include <functional>
#include "../ProjectileManager.h"

class GameManager
{
	static GameManager *gameManager;

	ProjectileManager *projectileManager;
	ResourceManager *resourceManager;
	GLFWwindow* _window;
	bool _running;
	RenderSystem *_renderSystem;
	float aspect = 1;
	float remainingReloadTime = 0;
	const float RELOAD_TIME = 2;
	static void windowResize(GLFWwindow* window, int width, int height);
	static void wrapperMouseClick(GLFWwindow* window, double xpos, double ypos);
	static void wrapperMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void processInput(GLFWwindow *windows, float dTime);

	GameManager(bool running, GLFWwindow* window, RenderSystem *renderSystem, ResourceManager* resourceManager, Scane* scane, ProjectileManager* projectileManager);
	~GameManager();
public:
	static GameManager& getGameManager();
	static void destroyGameManager();
	void runGameLoop();
};