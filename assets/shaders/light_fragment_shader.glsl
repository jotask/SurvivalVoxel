#version 450 core

layout(location = 0) out vec4 out_color;

in vec3 colour;

void main()
{
  out_color = vec4(colour, 1.0f);
  //out_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}