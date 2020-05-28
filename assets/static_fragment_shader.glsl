#version 450 core

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
    vec4 tex = texture(texture_diffuse_1, TexCoords);
    if(tex.x == 0 && tex.y == 0 && tex.z == 0)
    {
        tex = vec4(1.0f);
    }
    out_color = Colour * tex;
}
