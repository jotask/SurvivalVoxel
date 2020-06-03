#version 450 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec4 inColor;

out vec3 FragPos;
out vec3 Normal;
out vec4 Color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
  Color = inColor;
  FragPos = vec3(model * vec4(inPosition, 1.0));
  Normal = mat3(transpose(inverse(model))) * inNormal;
  gl_Position = projection * view * vec4(FragPos, 1.0);
}