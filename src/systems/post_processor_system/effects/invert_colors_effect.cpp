#include "invert_colors_effect.hpp"

#include "systems/shader_system/shader.hpp"

#include <array>

namespace aiko
{
    namespace postprocessing
    {

        InvertColorsFx::InvertColorsFx()
            : Effect("InvertColors")
        {

        }

        void InvertColorsFx::init(Shader* shader)
        {

        }

        void InvertColorsFx::use(Shader* shader)
        {
            shader->setBool("invertColors", isEnabled());
        }

    }
}
