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
            std::array<int, 9> edgeKernel = {
                -1, -1, -1,
                -1,  8, -1,
                -1, -1, -1
            };
            glUniform1iv(glGetUniformLocation(shader->getProgramId(), "edge_kernel"), static_cast<GLsizei>(edgeKernel.size()), edgeKernel.data());
        }

        void ConfuseFx::use(Shader* shader)
        {
            shader->setBool("confuse", isEnabled());
        }

    }
}
