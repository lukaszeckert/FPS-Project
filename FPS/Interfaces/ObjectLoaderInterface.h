#pragma once
#ifndef __ObjectLoaderInterface__h
#define __ObjectLoaderInterface__h

#include "..\Loaders\OBJ_Loader.h"
#include "..\Models\VertexData.h"

#include <iostream>
#include <vector>

class ObjectLoaderInterface
{
public:
	static std::vector<std::pair<std::string, std::vector<VertexData>>> loadObjFile(const char* filename);
	//ObjectLoaderInterface();
	//~ObjectLoaderInterface();
};

#endif // !__ObjectLoaderInterface__h
