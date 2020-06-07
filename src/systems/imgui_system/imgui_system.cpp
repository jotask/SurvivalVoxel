#include "imgui_system.hpp"

#include "systems/display_system.hpp"
#include "systems/imgui_system/imgui_console.hpp"

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>


namespace aiko
{
    ImguiSystem::ImguiSystem()
        : m_showDemoWindow(false)
        , m_showConsole(false)
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
        if (ImGui::BeginMenu("Debug"))
        {
            if (ImGui::MenuItem("Console", "", m_showConsole, true))
            {
                m_showConsole = !m_showConsole;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
        if (m_showDemoWindow == true)
        {
            ImGui::ShowDemoWindow(&m_showDemoWindow);
        }
        if (m_showConsole == true)
        {
            static AikoConsole console;
            console.draw(&m_showConsole);
        }
    }

    void ImguiSystem::beginFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImguiSystem::endFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImguiSystem::registerSystem(std::string name, bool& activated)
    {
        m_systemsEnabled.insert({ name, activated });
    }

}
