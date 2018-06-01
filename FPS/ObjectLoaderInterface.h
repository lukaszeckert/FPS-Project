#pragma once
#ifndef __ObjectLoaderInterface__h
#define __ObjectLoaderInterface__h

#include "OBJ_Loader.h"
#include <iostream>
#include "VertexData.h"
#include <vector>

class ObjectLoaderInterface
{
public:
	static std::vector<std::pair<std::string, std::vector<VertexData>>> loadObjFile(const char* filename);
	//ObjectLoaderInterface();
	//~ObjectLoaderInterface();
};

#endif // !__ObjectLoaderInterface__h
