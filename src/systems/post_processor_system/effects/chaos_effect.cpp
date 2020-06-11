#include "chaos_effect.hpp"

#include "systems/shader_system/shader.hpp"

#include <imgui.h>

#include <array>

namespace aiko
{
    namespace postprocessing
    {

        ChaosFx::ChaosFx()
            : Effect("Chaos")
            , m_strength(0.3f)
        {

        }

        void ChaosFx::init(Shader* shader)
        {

        }

        void ChaosFx::use(Shader* shader)
        {
            shader->setBool("chaos", isEnabled());
            shader->setFloat("chaosStrength", m_strength);
        }

        void ChaosFx::updateSettings()
        {
            constexpr const auto value = 2.0f;
            ImGui::SliderFloat("Chaos Strength", &m_strength, -value, value);
        }

    }
}
