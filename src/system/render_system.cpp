#include "system/render_system.hpp"

#include "system/display_system.hpp"
#include "system/imgui_system.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

namespace engine
{
    RenderSystem::RenderSystem()
        : m_displaySystem(nullptr)
        , m_renderImgui(false)
        , m_drawWireframes(false)
        , m_bgColor(1.f)
    {

    }

    bool RenderSystem::connect(SystemConnector & connector)
    {
        m_displaySystem = connector.findSystem<DisplaySystem>();
        m_imguiSystem = connector.findSystem<ImguiSystem>();
        return true;
    }

    bool RenderSystem::init()
    {
        m_imguiSystem->registerSystem("RenderSystem", m_renderImgui);
        glEnable(GL_DEPTH_TEST);
        return true;
    }

    void RenderSystem::render()
    {
        if (m_renderImgui == true)
        {
            ImGui::Begin("RenderSystem", &m_renderImgui);
            ImGui::Checkbox("Wireframe", &m_drawWireframes);
            ImGui::ColorEdit4("Bg", &m_bgColor.x);
            ImGui::End();
        }
    }

    void RenderSystem::beginFrame()
    {
        glClearColor(m_bgColor.x, m_bgColor.y, m_bgColor.z, m_bgColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (m_drawWireframes == true)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }

    void RenderSystem::swapBuffers() const
    {
        glfwSwapBuffers(m_displaySystem->getWindow());
    }

}
