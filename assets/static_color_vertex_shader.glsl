#version 450 core

struct Light
{
    vec3 position;
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 textureCoordinates;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform Light light;

out vec4 Colour;
out vec2 TexCoords;

void main()
{
  Colour = color;
  gl_Position = projection * view * model * vec4(position, 1.0);
}
