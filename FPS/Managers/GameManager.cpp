#include "GameManager.h"

GameManager *GameManager::gameManager = nullptr;


void GameManager::windowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height); //Obraz ma byÊ generowany w oknie o tej rozdzielczoúci
	auto &gm = getGameManager();
	if (height != 0) {
		gm.aspect = (float)width / (float)height; //Stosunek szerokoúci do wysokoúci okna
	}
	else {
		gm.aspect = 1;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, width, height);
}
void GameManager::wrapperMouseClick(GLFWwindow * window, double xpos, double ypos)
{
	auto &gm = GameManager::getGameManager();
	gm.mouse_callback(window, xpos, ypos);
}
void GameManager::mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	static double pxPos = -1;
	static double pyPos = -1;
	if (pxPos != -1)
	{
		resourceManager->getCamera()->processMouse(xpos - pxPos, pyPos - ypos);	
	}
	pxPos = xpos;
	pyPos = ypos;
	
}
void GameManager::processInput(GLFWwindow * window, float dTime)
{
	auto camera = resourceManager->getCamera();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->processMovement(FORWARD,dTime*4);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->processMovement(BACKWARD, dTime*4);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->processMovement(LEFT, dTime*4);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->processMovement(RIGHT, dTime*4);

}
GameManager& GameManager::getGameManager() {
	if (gameManager == nullptr)
	{




		GLFWwindow* window; //Wskaünik na obiekt reprezentujπcy okno
		glfwSetErrorCallback([](int, const char* str) {
			std::cout << "GLFW error: " << str << "\n";
		});
		if (!glfwInit()) { //Zainicjuj bibliotekÍ GLFW
			fprintf(stderr, "Nie moøna zainicjowaÊ GLFW.\n");
			exit(EXIT_FAILURE);
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		window = glfwCreateWindow(1280, 720, "LearnOpenGL", NULL, NULL); //UtwÛrz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

		if (!window) //Jeøeli okna nie uda≥o siÍ utworzyÊ, to zamknij program
		{
			fprintf(stderr, "Nie moøna utworzyÊ okna.\n");
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje siÍ aktywny i polecenia OpenGL bÍdπ dotyczyÊ w≥aúnie jego.
		glfwSwapInterval(1); //Czekaj na 1 powrÛt plamki przed pokazaniem ukrytego bufora
		glewExperimental = GL_TRUE; //Ubuntu


		if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekÍ GLEW
			fprintf(stderr, "Nie moøna zainicjowaÊ GLEW.\n");
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


		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetFramebufferSizeCallback(window, windowResize);
		glfwSetCursorPosCallback(window, wrapperMouseClick);

		glEnable(GL_DEPTH_TEST);
		
		gameManager = new GameManager(true,window, &RenderSystem::getRenderSystem(window)
		,&ResourceManager::getResourceManager(), new Scane());
		
		
	
		windowResize(window, 1280, 720);
		std::cout << glGetString(GL_VERSION);

	}
	return *gameManager;
}

void GameManager::destroyGameManager()
{
	if (gameManager != nullptr) {
		glfwTerminate();
		glfwDestroyWindow(gameManager->_window);
	
		delete gameManager;

	}
}

void GameManager::runGameLoop()
{
	float currentFrame = glfwGetTime();
	float lastFrame = glfwGetTime();
	float dTime = 0;
	while (_running){
		
		
		_renderSystem->renderAll(resourceManager->getEntityArray(), resourceManager->getCamera(), aspect);
		glfwPollEvents();
		currentFrame = glfwGetTime();
		dTime = currentFrame - lastFrame;
		std::cout << resourceManager->getCamera()->position.x << " " << resourceManager->getCamera()->position.y << " " << resourceManager->getCamera()->position.z << "\n";
		processInput(_window, dTime);
		lastFrame = currentFrame;
	}
}
GameManager::GameManager(bool running,GLFWwindow* window, RenderSystem* renderSystem, ResourceManager *resourceManager, Scane* scane)
: _running(running), _window(window), _renderSystem(renderSystem), resourceManager(resourceManager){
	scane->createScane();
	
};
GameManager::~GameManager() {
	RenderSystem::destroyRenderSystem();
	ResourceManager::destroyResourceManager();
};