#include "chaos_effect.hpp"

#include "systems/shader_system/shader.hpp"

#include <array>

namespace aiko
{
    namespace postprocessing
    {

        ChaosFx::ChaosFx()
            : Effect("Chaos")
        {

        }

        void ChaosFx::init(Shader* shader)
        {

        }

        void ChaosFx::use(Shader* shader)
        {
            shader->setBool("chaos", isEnabled());
        }

    }
}
