#include "system/imgui_system.hpp"

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include "system/display_system.hpp"

namespace engine
{
    ImguiSystem::ImguiSystem()
        : showDemoWindow(true)
        , m_displaySystem(nullptr)
    {

    }

    bool ImguiSystem::connect(SystemConnector & connector)
    {
        m_displaySystem = connector.findSystem<DisplaySystem>();
        return true;
    }

    bool ImguiSystem::init()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGui::StyleColorsDark();

        auto* window = m_displaySystem->getWindow();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");

        return true;

    }

    void ImguiSystem::preUpdate()
    {

    }

    void ImguiSystem::update()
    {

    }

    void ImguiSystem::postUpdate()
    {

    }

    void ImguiSystem::preRender()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImguiSystem::render()
    {

    }

    void ImguiSystem::postRender()
    {
        if (showDemoWindow == true)
        {
            ImGui::ShowDemoWindow(&showDemoWindow);
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

}
