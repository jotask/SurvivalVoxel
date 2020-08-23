#include "mandelbrot_effect.hpp"

#include "systems/shader_system/shader.hpp"

#include <imgui.h>

#include <array>

namespace aiko
{
    namespace postprocessing
    {

        MandelbrotFx::MandelbrotFx()
            : Effect("Mandelbrot")

        {

        }

        void MandelbrotFx::init(Shader* shader)
        {

        }

        void MandelbrotFx::use(Shader* shader)
        {
            shader->setBool("mandrelbot", isEnabled());
        }

        void MandelbrotFx::updateSettings()
        {

        }

    }
}
