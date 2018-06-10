#pragma once

#include <string>
#include <vector>
#include "../Models/VertexData.h"
#include "../Models/Texture.h"
#include "../Models/VertexBuffer.h"

class Mesh {
public:
  glm::vec3 color;
  std::string name;
  std::vector<VertexData> points; //TODO we probably don't need that
  Texture *tex, *tex_spec;
  float shiniess;
  VertexBuffer *vertexBuffer;

  Mesh(std::string name, std::vector<VertexData> points, Texture *tex, Texture *tex_spec);
  ~Mesh();
};