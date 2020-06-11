#include "blur_effect.hpp"

#include "systems/shader_system/shader.hpp"

#include <array>

namespace aiko
{
    namespace postprocessing
    {

        BlurFx::BlurFx()
            : Effect("Blur")
        {

        }

        void BlurFx::init(Shader* shader)
        {
            std::array<float, 9> blurKernel = {
                1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
                2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
                1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
            };
            glUniform1fv(glGetUniformLocation(shader->getProgramId(), "blur_kernel"), static_cast<GLsizei>(blurKernel.size()), blurKernel.data());
        }

        void BlurFx::use(Shader* shader)
        {
            shader->setBool("blur", isEnabled());
        }

    }
}
