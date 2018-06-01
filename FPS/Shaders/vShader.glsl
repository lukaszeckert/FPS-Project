#version 330 core

attribute vec4 aPostionVertex;
attribute vec4 aNormal;
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


void main()
{
    gl_Position = P*V*M*aPostionVertex;
}