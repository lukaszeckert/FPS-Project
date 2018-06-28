#include "../Models/Mesh.h"
#include <iostream>

Mesh::Mesh(std::string name, std::vector<VertexData> points, Texture *tex, Texture *tex_spec) :
  name{name}, tex{tex}, tex_spec{tex_spec}
  {
    vertexBuffer = new VertexBuffer(points.data(), sizeof(VertexData)*points.size(), GL_TRIANGLES, points.size(), sizeof(VertexData));
    shape = new btConvexHullShape();
    for(auto point: points) {
      shape->addPoint(btVector3(point.postion.x, point.postion.y, point.postion.z));
    }
//    shape->optimizeConvexHull();    
  }

Mesh::~Mesh() {
  delete vertexBuffer;
}