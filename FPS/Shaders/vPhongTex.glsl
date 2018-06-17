#version 330 core
attribute vec4 aPostionVertex;
attribute vec4 aNormal;
attribute vec2 aTexCoords;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

out vec4 Normal;
out vec4 FragPos;
out vec2 TexCoords;
void main()
{
    gl_Position = P*V*M*aPostionVertex;
	FragPos = vec4(M*aPostionVertex);
	Normal = norlmalize(transpose(inverse(M))*aNormal);
	TexCoords = aTexCoords;
	//gl_Position = P*V*M*vec4(aTexCoords,-3,1);
}