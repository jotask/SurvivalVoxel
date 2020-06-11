#include "shake_effect.hpp"

#include "systems/shader_system/shader.hpp"

#include <imgui.h>

#include <array>

namespace aiko
{
    namespace postprocessing
    {

        ShakeFx::ShakeFx()
            : Effect("Shake")
            , m_strength(0.01f)
        {

        }

        void ShakeFx::init(Shader* shader)
        {
        }

        void ShakeFx::use(Shader* shader)
        {
            shader->setBool("shake", isEnabled());
            shader->setFloat("shakeStrength", m_strength);
        }

        void ShakeFx::updateSettings()
        {
            constexpr const auto value = 1.0f;
            ImGui::SliderFloat("Shake Strength", &m_strength, -value, value);
        }

    }
}
