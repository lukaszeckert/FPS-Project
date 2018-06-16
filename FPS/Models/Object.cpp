#include "../Models/Object.h"

Object::Object() {
  shape = new btConvexHullShape();
}

Object::~Object() {
  delete shape;
  for(auto it: meshes) {
    delete it;
  }
}

void Object::addMesh(Mesh* mesh) {
  meshes.push_back(mesh);
  for(auto point: mesh->points) {
    shape->addPoint(btVector3(point.postion.x, point.postion.y, point.postion.z));
  }
}

void Object::optimize() {
  shape->optimizeConvexHull();
}