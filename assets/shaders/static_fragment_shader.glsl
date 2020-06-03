#version 450 core

struct Camera
{
    vec3 positon;
};

struct Light
{
    vec3 position;
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec4 Colour;
in vec2 TexCoords;

out vec4 out_color;

uniform sampler2D texture_diffuse_1;
uniform Light light;

void main()
{
    out_color = Colour * texture(texture_diffuse_1, TexCoords);
}
