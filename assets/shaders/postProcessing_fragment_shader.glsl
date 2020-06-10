#version 450 core
in  vec2  TexCoords;
out vec4  color;

const int KERNEL_SIZE = 9;

uniform sampler2D scene;
uniform vec2      offsets[KERNEL_SIZE];
uniform int       edge_kernel[KERNEL_SIZE];
uniform float     blur_kernel[KERNEL_SIZE];

uniform bool chaos;
uniform bool confuse;
uniform bool shake;

void main()
{


    color = vec4(0.0f);
    vec3 samplers[KERNEL_SIZE];
    // sample from texture offsets if using convolution matrix
    if(chaos || shake)
    {
       for(int i = 0; i < KERNEL_SIZE; i++)
       {
            samplers[i] = vec3(texture(scene, TexCoords.st + offsets[i]));
       }
    }

    // process effects
    if (chaos)
    {
        for(int i = 0; i < KERNEL_SIZE; i++)
        {
            color += vec4(samplers[i] * edge_kernel[i], 0.0f);
        }
        color.a = 1.0f;
    }
    else if (confuse)
    {
        color = vec4(1.0 - texture(scene, TexCoords).rgb, 1.0);
    }
    else if (shake)
    {
        for(int i = 0; i < KERNEL_SIZE; i++)
        {
            color += vec4(samplers[i] * blur_kernel[i], 0.0f);
        }
        color.a = 1.0f;
    }
    else
    {
        color =  texture(scene, TexCoords);
    }
}