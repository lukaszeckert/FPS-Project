#include "../Models/Object.h"

Object::~Object() {
  for(auto it: meshes) {
    delete it;
  }
}

void Object::addMesh(Mesh* mesh) {
  meshes.push_back(mesh);
}