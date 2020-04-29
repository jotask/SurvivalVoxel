#version 450 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec4 in_color;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform vec3 u_lightPos;
uniform vec3 u_lightCol;

out vec4 color;
out vec3 fragPos;
out vec3 normal;
out vec3 lightPos;
out vec3 lightCol;

void main()
{

  color = in_color;
  normal = in_normal;
  lightPos = u_lightPos;
  lightCol = u_lightCol;
  fragPos = vec3(model_matrix * vec4(in_position, 1.0f));

  gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1);

}