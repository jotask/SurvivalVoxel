#include "systems/assets_system/assets_system.hpp"

#include "systems/imgui_system.hpp"

#include <imgui.h>

namespace aiko
{
    AssetsSystem::AssetsSystem()
        : m_imguiSystem(nullptr)
        , m_renderImgui(false)
    {

    }

    bool AssetsSystem::connect(SystemConnector & connector)
    {
        m_imguiSystem = connector.findSystem<ImguiSystem>();
        return true;
    }

    bool AssetsSystem::init()
    {
        m_imguiSystem->registerSystem("AssetsSystem", m_renderImgui);
        return true;

    }

    void AssetsSystem::render()
    {
        if (m_renderImgui == true)
        {
            ImGui::Begin("AssetsSystem", &m_renderImgui);

            ImGui::End();
        }
    }

}
