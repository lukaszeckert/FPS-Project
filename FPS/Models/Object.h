#pragma once

#include <vector>
#include <string>
#include "../Models/Mesh.h"
#include "../Models/VertexData.h"
#include "../Models/Texture.h"

class Object {
  public:
    std::vector<Mesh*> meshes;
    ~Object();
    void addMesh(Mesh* mesh);
};