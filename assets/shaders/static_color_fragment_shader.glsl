#version 450 core

struct Light
{
    vec3 position;
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 pass_textureCoordinates;
in vec3 surfaceNormal;
in vec3 toLightVector;

out vec4 out_color;

uniform Light light;

void main()
{

    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitLightVector = normalize(toLightVector);

    float nDot1 = dot(unitNormal, unitLightVector);
    float brightness = max(nDot1, 0.0f);

    vec3 diffuse = brightness * light.color;

    out_color = vec4(diffuse, 1.0f);
}
