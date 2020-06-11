#include "edge_effect.hpp"

#include "systems/shader_system/shader.hpp"

#include <array>

namespace aiko
{
    namespace postprocessing
    {

        EdgeFx::EdgeFx()
            : Effect("Edge")
        {

        }

        void EdgeFx::init(Shader* shader)
        {
            std::array<int, 9> edgeKernel = {
                -1, -1, -1,
                -1,  8, -1,
                -1, -1, -1
            };
            glUniform1iv(glGetUniformLocation(shader->getProgramId(), "edge_kernel"), static_cast<GLsizei>(edgeKernel.size()), edgeKernel.data());
        }

        void EdgeFx::use(Shader* shader)
        {
            shader->setBool("edge", isEnabled());
        }

    }
}
