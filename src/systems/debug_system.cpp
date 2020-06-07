#include "systems/debug_system.hpp"

#include "systems/imgui_system/imgui_system.hpp"
#include "systems/shader_system/shader_system.hpp"

#include <imgui.h>
#include <GLFW/glfw3.h>

namespace aiko
{
    DebugSystem::DebugSystem()
        : m_renderImgui(false)
        , m_imguiSystem(nullptr)
        , m_shaderSystem(nullptr)
        , m_fps(0)
        , m_previousTime(0.0)
        , m_framCount(0)
    {

    }

    bool DebugSystem::connect(SystemConnector & connector)
    {
        m_imguiSystem = connector.findSystem<ImguiSystem>();
        m_shaderSystem = connector.findSystem<ShaderSystem>();

        return true;
    }

    bool DebugSystem::init()
    {
        m_imguiSystem->registerSystem("DebugSystem", m_renderImgui);
        return true;
    }

    void DebugSystem::preUpdate()
    {

    }

    void DebugSystem::update()
    {
        const auto currentTime = glfwGetTime();
        m_framCount++;
        if (currentTime - m_previousTime >= 1.0)
        {
            m_fps = static_cast<double>(m_framCount) / (currentTime - m_previousTime);
            m_previousTime = currentTime;
            m_framCount = 0;
        }
    }

    void DebugSystem::postUpdate()
    {

    }

    void DebugSystem::preRender()
    {

    }

    void DebugSystem::render()
    {
        if (m_renderImgui == true)
        {
            ImGui::Begin("DebugSystem", &m_renderImgui);
            ImGui::Text("FPS: %lf", m_fps);
            ImGui::End();
        }
    }

    void DebugSystem::postRender()
    {

    }

    const double DebugSystem::getFps() const
    {
        return m_fps;
    }

}
