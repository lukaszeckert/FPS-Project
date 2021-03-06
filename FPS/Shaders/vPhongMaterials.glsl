#version 330 core
attribute vec4 aPostionVertex;
attribute vec4 aNormal;
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

out vec4 Normal;
out vec4 FragPos;

void main()
{
    gl_Position = P*V*M*aPostionVertex;
	FragPos = vec4(M*aPostionVertex);
	Normal = aNormal;
}