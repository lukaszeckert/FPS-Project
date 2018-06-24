#pragma once

#include <string>
#include <vector>
#include <bullet/btBulletDynamicsCommon.h>
#include "../Models/VertexData.h"
#include "../Models/Texture.h"
#include "../Models/VertexBuffer.h"

class Mesh {
public:
  glm::vec3 color;
  std::string name;
  btConvexHullShape* shape;  
  Texture *tex, *tex_spec;
  float shiniess;
  VertexBuffer *vertexBuffer;

  Mesh(std::string name, std::vector<VertexData> points, Texture *tex, Texture *tex_spec);
  ~Mesh();
};