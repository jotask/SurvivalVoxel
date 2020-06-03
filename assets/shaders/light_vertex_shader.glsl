#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 textureCoordinates;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 lightPos;
uniform vec3 lightColor;

out vec3 colour;

void main()
{
  colour = lightColor;
  gl_Position = projection * view * vec4(position, 1.0f);
}