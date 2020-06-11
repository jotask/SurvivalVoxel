#include "confuse_effect.hpp"

#include "systems/shader_system/shader.hpp"

#include <array>

namespace aiko
{
    namespace postprocessing
    {

        ConfuseFx::ConfuseFx()
            : Effect("Confuse")
        {

        }

        void ConfuseFx::init(Shader* shader)
        {

        }

        void ConfuseFx::use(Shader* shader)
        {
            shader->setBool("confuse", isEnabled());
        }

    }
}
