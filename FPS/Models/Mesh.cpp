#include "../Models/Mesh.h"

Mesh::Mesh(std::string name, std::vector<VertexData> points, Texture *tex, Texture *tex_spec) :
  name{name}, points{points}, tex{tex}, tex_spec{tex_spec}
  {
	vertexBuffer = new VertexBuffer(points.data(), sizeof(VertexData)*points.size(), GL_TRIANGLES, points.size(), sizeof(VertexData));
  }

Mesh::~Mesh() {

  delete vertexBuffer;
}