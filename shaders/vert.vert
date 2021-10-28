#version 330 core

layout (location = 0) in vec3 aPos;
out vec4 gl_Position;

uniform mat4 MATRIX_MVP;

void main()
{
   gl_Position = MATRIX_MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0) ;
} 