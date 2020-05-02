#include "system/imgui_system.hpp"

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include "system/display_system.hpp"

namespace engine
{
    ImguiSystem::ImguiSystem()
        : m_showDemoWindow(false)
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

        registerSystem("ImGuiSystem", m_showDemoWindow);

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
        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("Systems"))
        {
            for (auto& entry : m_systemsEnabled)
            {
                if (ImGui::MenuItem(entry.first.c_str(), "", entry.second, true))
                {
                    entry.second = !entry.second;
                }
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    void ImguiSystem::postRender()
    {
        if (m_showDemoWindow == true)
        {
            ImGui::ShowDemoWindow(&m_showDemoWindow);
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImguiSystem::registerSystem(std::string name, bool& activated)
    {
        m_systemsEnabled.insert({ name, activated });
    }

}
