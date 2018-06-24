#include "../Models/Object.h"

Object::Object() {
  shape = new btCompoundShape();
}

Object::~Object() {
  delete shape;
  for(auto it: meshes) {
    delete it;
  }
}

void Object::addMesh(Mesh* mesh) {
  meshes.push_back(mesh);
  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(btVector3(0,0,0));
  shape->addChildShape(transform, mesh->shape);
}