#version 450 core

const int MAX_LIGHT_NUMBER = 4;

struct Light
{
    vec3 position;
    vec3 color;
};

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 textureCoordinates;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform Light light[MAX_LIGHT_NUMBER];

out vec3 surfaceNormal;
out vec3 toLightVector[MAX_LIGHT_NUMBER];
out vec3 toCameraVector;

void main()
{
  vec4 worldPosition = model * vec4(position, 1.f);
  gl_Position = projection * view * worldPosition;
  surfaceNormal = (model * vec4(normal, 0.0f)).xyz;
  for(int i = 0 ; i < MAX_LIGHT_NUMBER; i++)
  {
    toLightVector[i] = light[i].position - worldPosition.xyz;
  }
  toCameraVector = (inverse(view) * vec4(0.0, 0.0f, 0.0, 1.0f)).xyz - worldPosition.xyz;
}
