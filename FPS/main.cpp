//#include "Dependencies\glew\glew.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\glfw\glfw3.h"

//#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include <stdio.h>
#include "Managers\GameManager.h"
#include "Dependencies\glm\vec3.hpp"
#include "Dependencies\glm\glm.hpp"
#include <fstream>

/*
bool initGL()
{
	PIXELFORMATDESCRIPTOR pfd;
	HWND hwnd; HDC hdc; int pixelFormat;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 2;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	hwnd = CreateWindowEx(WS_EX_TOOLWINDOW, "STATIC", "glctx",
		WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		0, 0, 640, 480, 0, 0, GetModuleHandle(NULL), 0);
	if (!hwnd) return false;
	ShowWindow(hwnd, SW_HIDE);

	hdc = GetDC(hwnd);
	pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);
	wglMakeCurrent(hdc, wglCreateContext(hdc));
	return wglGetCurrentContext() != NULL;
}*/

int main(int argc, char **argv)
{
	//initGL();
	
	GameManager *gameManager = &GameManager::getGameManager();
	gameManager->runGameLoop();
	GameManager::destroyGameManager();
	for (int i = 0; i < 100000000; i += 2)
		i--;
	return 0;
}