#version 450 core

layout (location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 lightColor;

out vec3 colour;

void main()
{
  colour = lightColor;
  gl_Position = projection * view * model * vec4(position, 1.0f);
}