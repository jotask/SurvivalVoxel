#include "shake_effect.hpp"

#include "systems/shader_system/shader.hpp"

#include <array>

namespace aiko
{
    namespace postprocessing
    {

        ShakeFx::ShakeFx()
            : Effect("Shake")
        {

        }

        void ShakeFx::init(Shader* shader)
        {
        }

        void ShakeFx::use(Shader* shader)
        {
            shader->setBool("shake", isEnabled());
        }

    }
}
