#include "VertexData.h"



VertexData::VertexData(glm::vec3 postion, glm::vec3 normal): postion(glm::vec4(postion,1.0f)),normal(glm::vec4(normal,0.0f))
{
}


VertexData::~VertexData()
{
}
