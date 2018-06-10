#pragma once

#include <string>
#include <vector>
#include "../Models/VertexData.h"
#include "../Models/Texture.h"

class Mesh {
public:
  std::string name;
  std::vector<VertexData> points;
  Texture *tex, *tex_spec;

  Mesh(std::string name, std::vector<VertexData> points, Texture *tex, Texture *tex_spec);
  ~Mesh();
};