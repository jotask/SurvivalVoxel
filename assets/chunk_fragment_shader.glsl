#version 450 core
layout(location = 0) out vec4 out_color;

in vec4 color;
in vec3 normal;
in vec3 fragPos;
in vec3 lightPos;
in vec3 lightCol;

void main()
{

  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPos - fragPos);

  float diff = max(dot(norm, lightDir), 0.0f);
  vec3 diffuse = diff * lightCol;

  // vec3 result = (ambient + diffuse) * color.xyz;
  vec3 result = (diffuse) * color.xyz;

  out_color = vec4(result, 1.0f);

}