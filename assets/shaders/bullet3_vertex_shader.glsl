#version 450 core
in vec3 inPosition;

uniform mat4 projection;
uniform mat4 view;

void main()
{
  gl_Position = projection * view * vec4(inPosition, 1.0);
}