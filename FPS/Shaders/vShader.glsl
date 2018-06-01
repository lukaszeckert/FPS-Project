#version 330 core

layout (location = 0) in vec4 aPostionVertex;
layout (location = 1) in vec4 aNormal;
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;



void main()
{
    gl_Position = P*V*M*aPostionVertex;

}