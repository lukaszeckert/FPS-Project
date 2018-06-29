#include "GameManager.h"

GameManager *GameManager::gameManager = nullptr;


void GameManager::windowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height); //Obraz ma by� generowany w oknie o tej rozdzielczo�ci
	auto &gm = getGameManager();
	if (height != 0) {
		gm.aspect = (float)width / (float)height; //Stosunek szeroko�ci do wysoko�ci okna
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
void GameManager::wrapperMouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
	
	auto &gm = GameManager::getGameManager();
	gm.mouse_button_callback(window, button, action, mods);
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
void GameManager::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		if (remainingReloadTime <= 0)
		{
			remainingReloadTime = RELOAD_TIME;
			auto camera = resourceManager->getCamera();
			projectileManager->createProjectile(camera->getPosition(), camera->dir, 50, glm::vec3(0.0, 1.0, 0.0));
		}
}
void GameManager::processInput(GLFWwindow * window, float dTime)
{
	int mask = 0;
	auto camera = resourceManager->getCamera();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		mask += FORWARD;
//		camera->processMovement(FORWARD,dTime*4);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mask += BACKWARD;
	//	camera->processMovement(BACKWARD, dTime*4);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mask += LEFT;
//		camera->processMovement(LEFT, dTime*4);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mask += RIGHT;
//		camera->processMovement(RIGHT, dTime*4);
	camera->processMovement(mask, dTime * 4);


}
GameManager& GameManager::getGameManager() {
	if (gameManager == nullptr)
	{




		GLFWwindow* window; //Wska�nik na obiekt reprezentuj�cy okno
		glfwSetErrorCallback([](int, const char* str) {
			std::cout << "GLFW error: " << str << "\n";
		});
		if (!glfwInit()) { //Zainicjuj bibliotek� GLFW
			fprintf(stderr, "Nie mo�na zainicjowa� GLFW.\n");
			exit(EXIT_FAILURE);
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		window = glfwCreateWindow(1280, 720, "LearnOpenGL", NULL, NULL); //Utw�rz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

		if (!window) //Je�eli okna nie uda�o si� utworzy�, to zamknij program
		{
			fprintf(stderr, "Nie mo�na utworzy� okna.\n");
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje si� aktywny i polecenia OpenGL b�d� dotyczy� w�a�nie jego.
		glfwSwapInterval(1); //Czekaj na 1 powr�t plamki przed pokazaniem ukrytego bufora
		glewExperimental = GL_TRUE; //Ubuntu


		if (glewInit() != GLEW_OK) { //Zainicjuj bibliotek� GLEW
			fprintf(stderr, "Nie mo�na zainicjowa� GLEW.\n");
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
		glfwSetMouseButtonCallback(window, wrapperMouseButtonCallback);
		glEnable(GL_DEPTH_TEST);
		
		gameManager = new GameManager(true,window, &RenderSystem::getRenderSystem(window)
		,&ResourceManager::getResourceManager(), new Scane(), &ProjectileManager::getProjectileManager(), &EnemyManager::getEnemyManager());
		
		
	
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
		currentFrame = glfwGetTime();
		dTime = currentFrame - lastFrame;
		projectileManager->update(dTime);
		enemyManager->update(dTime);
		resourceManager->dynamicsWorld->stepSimulation(1.0f/60.0f, 1);
		LightSystem::getLightSystem()->update();
		
		_running = !glfwWindowShouldClose(_window);

		_renderSystem->renderAll(resourceManager->getEntityArray(), resourceManager->getCamera(), aspect);
		glfwPollEvents();
		processInput(_window, dTime);
		remainingReloadTime = std::max(0.0f, remainingReloadTime - dTime);
		lastFrame = currentFrame;
	}
}
GameManager::GameManager(bool running,GLFWwindow* window, RenderSystem* renderSystem, ResourceManager *resourceManager, Scane* scane, ProjectileManager* projectileManager, EnemyManager* enemyManager)
: _running(running), _window(window), _renderSystem(renderSystem), resourceManager(resourceManager), projectileManager(projectileManager),enemyManager(enemyManager){
	scane->createScane();
	
};
GameManager::~GameManager() {
	RenderSystem::destroyRenderSystem();
	ResourceManager::destroyResourceManager();
};