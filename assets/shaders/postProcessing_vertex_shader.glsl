#version 450 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform float time;
uniform bool chaos;
uniform bool shake;
uniform bool blur;
uniform bool edge;
uniform bool invertColors;
uniform bool mandrelbot;

uniform float chaosStrength;
uniform float shakeStrength;

void main()
{

    if(mandrelbot == true)
    {
        gl_Position = vec4(vertex.xy, 0.0f, 1.0f); 
        TexCoords = vertex.zw;
        return;
    }

    gl_Position = vec4(vertex.xy, 0.0f, 1.0f); 
    vec2 texture = vertex.zw;
    if (chaos)
    {
        vec2 pos = vec2(texture.x + sin(time) * chaosStrength, texture.y + cos(time) * chaosStrength);
        TexCoords = pos;
    }
    else
    {
        TexCoords = texture;
    }
    if (shake)
    {
        gl_Position.x += cos(time * 10) * shakeStrength;
        gl_Position.y += cos(time * 15) * shakeStrength;
    }
} 