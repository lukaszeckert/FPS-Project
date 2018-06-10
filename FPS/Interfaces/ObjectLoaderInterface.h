#pragma once
#ifndef __ObjectLoaderInterface__h
#define __ObjectLoaderInterface__h

#include "../Loaders/OBJ_Loader.h"
#include "../Models/VertexData.h"
#include "../Models/Object.h"
#include "../Models/Texture.h"
#include "../Managers/ResourceManager.h"

#include <iostream>
#include <vector>

class ObjectLoaderInterface
{
public:
	static Object* loadObjFile(const char* filename, std::vector<Texture *> *TextureArray);
	//ObjectLoaderInterface();
	//~ObjectLoaderInterface();
};

#endif // !__ObjectLoaderInterface__h
