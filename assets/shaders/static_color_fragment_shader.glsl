#version 450 core

const int MAX_LIGHT_NUMBER = 4;

struct Light
{
    vec3 position;
    vec3 color;
};

in vec3 surfaceNormal;
in vec3 toLightVector[MAX_LIGHT_NUMBER];
in vec3 toCameraVector;

out vec4 out_color;

uniform Light light[MAX_LIGHT_NUMBER];

uniform float shineDamper;
uniform float reflectivity;

void main()
{

    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitVectorToCamera = normalize(toCameraVector);

    vec3 totalDiffuse = vec3(0.0f);
    vec3 totalSpecular = vec3(0.0f);

    for(int i = 0 ; i < MAX_LIGHT_NUMBER ; i++)
    {
        vec3 unitLightVector = normalize(toLightVector[i]);
        float nDot1 = dot(unitNormal, unitLightVector);
        float brightness = max(nDot1, 0.0f);
        vec3 lightDirection = -unitLightVector;
        vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
        float specularFactor = max(dot(reflectedLightDirection, unitVectorToCamera), 0.0f);
        float dampedFactor = pow(specularFactor, shineDamper);
        totalDiffuse = totalDiffuse + brightness * light[i].color;
        totalSpecular = totalSpecular + dampedFactor * reflectivity * light[i].color;
    }

    totalDiffuse = max(totalDiffuse, 0.2);

    out_color = vec4(totalDiffuse, 1.0f) + vec4(totalSpecular, 1.0f);

}
