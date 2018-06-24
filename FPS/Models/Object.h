#pragma once

#include <vector>
#include <string>
#include <bullet/btBulletDynamicsCommon.h>
#include "../Models/Mesh.h"
#include "../Models/VertexData.h"
#include "../Models/Texture.h"

class Object {
  public:
    std::vector<Mesh*> meshes;
    btCompoundShape *shape;
    Object();
    ~Object();
    void addMesh(Mesh* mesh);
};