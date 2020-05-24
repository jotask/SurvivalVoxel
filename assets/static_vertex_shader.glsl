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

out vec2 pass_textureCoordinates;
out vec3 surfaceNormal;
out vec3 toLightVector;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform Light light;

void main()
{

  vec4 worldPosition = model * vec4(position, 1.0);
  gl_Position = projection * view * model * worldPosition;

  pass_textureCoordinates = textureCoordinates;

  surfaceNormal = (model * vec4(normal, 0.f)).xyz;
  toLightVector = light.position - worldPosition.xyz;

}