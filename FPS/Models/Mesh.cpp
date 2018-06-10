#include "../Models/Mesh.h"

Mesh::Mesh(std::string name, std::vector<VertexData> points, Texture *tex, Texture *tex_spec) :
  name{name}, points{points}, tex{tex}, tex_spec{tex_spec}
  {

  }

Mesh::~Mesh() {
  delete tex;
  delete tex_spec;
}