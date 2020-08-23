#version 450 core
in  vec2  TexCoords;
out vec4  color;

const int KERNEL_SIZE = 9;

uniform sampler2D scene;
uniform vec2      offsets[KERNEL_SIZE];
uniform int       edge_kernel[KERNEL_SIZE];
uniform float     blur_kernel[KERNEL_SIZE];

uniform float time;
uniform bool chaos;
uniform bool shake;
uniform bool blur;
uniform bool edge;
uniform bool invertColors;
uniform bool mandrelbot;

void main()
{

    color = vec4(0.0f);

    if(mandrelbot == true)
    {
        color = vec4(sin(time), cos(time), sin(time), 1.0f);
        return;
    }

    vec3 samplers[KERNEL_SIZE];

    // sample from texture offsets if using convolution matrix
    for(int i = 0; i < KERNEL_SIZE; i++)
    {
        samplers[i] = vec3(texture(scene, TexCoords.st + offsets[i]));
    }

    // process effects
    if (edge)
    {
        for(int i = 0; i < KERNEL_SIZE; i++)
        {
            color += vec4(samplers[i] * edge_kernel[i], 0.0f);
        }
        color.a = 1.0f;
    }
    else if (blur)
    {
        for(int i = 0; i < KERNEL_SIZE; i++)
        {
            color += vec4(samplers[i] * blur_kernel[i], 0.0f);
        }
        color.a = 1.0f;
    }
    else if (invertColors)
    {
        color = vec4(1.0 - texture(scene, TexCoords).rgb, 1.0);
    }
    else if (shake)
    {
        color = vec4(texture(scene, TexCoords).rgb, 1.0);
    }
    else
    {
        color =  texture(scene, TexCoords);
    }
}