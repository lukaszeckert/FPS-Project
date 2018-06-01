#include "GameManager.h"

GameManager *GameManager::gameManager = nullptr;


void GameManager::windowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height); //Obraz ma byæ generowany w oknie o tej rozdzielczoœci
	auto &gm = getGameManager();
	if (height != 0) {
		gm.aspect = (float)width / (float)height; //Stosunek szerokoœci do wysokoœci okna
	}
	else {
		gm.aspect = 1;
	}
}
GameManager& GameManager::getGameManager() {
	std::cout << "Get\n";
	if (gameManager == nullptr)
	{
		std::cout << "Create\n";
		glfwInit();
		glewInit();
		
		//glfwWindowHint(GLFW_DEPTH_BITS, 24);
		//glfwWindowHint(GLFW_RED_BITS, 8);
		//glfwWindowHint(GLFW_GREEN_BITS, 8);
		//glfwWindowHint(GLFW_BLUE_BITS, 8);
		//glfwWindowHint(GLFW_ALPHA_BITS, 8);

	
		glEnable(GL_DEPTH_TEST);


		GLFWwindow *window = glfwCreateWindow(1280, 720, "DOOM", NULL, NULL);
		glfwMakeContextCurrent(window);
		
		gameManager = new GameManager(true,window, &RenderSystem::getRenderSystem(window)
		,&ResourceManager::getResourceManager());
		glfwSetFramebufferSizeCallback(window, windowResize);
		windowResize(window, 1280, 720);

	}
	return *gameManager;
}

void GameManager::destroyGameManager()
{
	std::cout << "Destroy\n";
	if (gameManager != nullptr) {
		glfwTerminate();
		glfwDestroyWindow(gameManager->_window);
		delete gameManager;

	}
}

void GameManager::runGameLoop()
{
	while (_running){
		_running = !glfwWindowShouldClose(_window);

		_renderSystem->renderAll(resourceManager->getEntityArray(), resourceManager->getCamera(), aspect);
		glfwPollEvents();
	}
}
GameManager::GameManager(bool running,GLFWwindow* window, RenderSystem* renderSystem, ResourceManager *resourceManager)
: _running(running), _window(window), _renderSystem(renderSystem), resourceManager(resourceManager){
	resourceManager->getCamera()->position = glm::vec3(2.0f, 0.0f, -3.0f);
	resourceManager->getCamera()->dir = glm::vec3(2.0, 0.0, 0.0);
	resourceManager->getCamera()->up = glm::vec3(0.0f, 1.0f, 0.0f);
	
};
GameManager::~GameManager() {
	RenderSystem::destroyRenderSystem();
	ResourceManager::destroyResourceManager();
};