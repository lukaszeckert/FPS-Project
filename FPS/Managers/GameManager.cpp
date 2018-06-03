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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, width, height);
}
GameManager& GameManager::getGameManager() {
	if (gameManager == nullptr)
	{




		GLFWwindow* window; //WskaŸnik na obiekt reprezentuj¹cy okno
		glfwSetErrorCallback([](int, const char* str) {
			std::cout << "GLFW error: " << str << "\n";
		});
		if (!glfwInit()) { //Zainicjuj bibliotekê GLFW
			fprintf(stderr, "Nie mo¿na zainicjowaæ GLFW.\n");
			exit(EXIT_FAILURE);
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		window = glfwCreateWindow(1280, 720, "LearnOpenGL", NULL, NULL); //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

		if (!window) //Je¿eli okna nie uda³o siê utworzyæ, to zamknij program
		{
			fprintf(stderr, "Nie mo¿na utworzyæ okna.\n");
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje siê aktywny i polecenia OpenGL bêd¹ dotyczyæ w³aœnie jego.
		glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora
		glewExperimental = GL_TRUE; //Ubuntu


		if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekê GLEW
			fprintf(stderr, "Nie mo¿na zainicjowaæ GLEW.\n");
			exit(EXIT_FAILURE);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

															 // glfw window creation
															 // --------------------
		
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			exit(-1);
		}	
		glfwSetFramebufferSizeCallback(window, windowResize);
		glEnable(GL_DEPTH_TEST);
		
		gameManager = new GameManager(true,window, &RenderSystem::getRenderSystem(window)
		,&ResourceManager::getResourceManager());
		
	
		windowResize(window, 1280, 720);
		std::cout << glGetString(GL_VERSION);

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
	resourceManager->getCamera()->position = glm::vec3(4.0f, 0.0f, -3.0f);
	resourceManager->getCamera()->dir = glm::vec3(2.0, 0.0, 0.0);
	resourceManager->getCamera()->up = glm::vec3(0.0f, 1.0f, 0.0f);
	
};
GameManager::~GameManager() {
	RenderSystem::destroyRenderSystem();
	ResourceManager::destroyResourceManager();
};