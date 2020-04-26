#include "engine.hpp"

#include "system/display_system.hpp"
#include "system/render_system.hpp"
#include "system/imgui_system.hpp"
#include "system/input_system.hpp"
#include "system/system_connector.hpp"

#include <algorithm>

// TODO : Remove this dependency and use some event system to remove dependency between system
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine
{
    Engine::Engine()
        : m_displaySystem(nullptr)
        , m_renderSystem(nullptr)
    {

    }

    void Engine::run()
    {

        init();

        auto* window = m_displaySystem->getWindow();

        while (glfwWindowShouldClose(window) == false)
        {

            // Update all systems
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->preUpdate(); });
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->update(); });
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->postUpdate(); });

            // TODO : This can be moved to their proper class
            int display_w = 0;
            int display_h = 0;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClear(GL_COLOR_BUFFER_BIT);

            // Render all systems
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->preRender(); });
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->render(); });
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->postRender(); });

            glfwSwapBuffers(window);
        }

    }

    void Engine::init()
    {

        // Create all systems first
        m_systems.push_back(std::make_unique<DisplaySystem>());
        m_systems.push_back(std::make_unique<RenderSystem>());
        m_systems.push_back(std::make_unique<ImguiSystem>());
        m_systems.push_back(std::make_unique<InputSystem>());

        // Connect all system before we initialize them
        auto systemConnector = SystemConnector(m_systems);
        m_displaySystem = systemConnector.findSystem<DisplaySystem>();
        m_renderSystem = systemConnector.findSystem<RenderSystem>();
        std::for_each(m_systems.begin(), m_systems.end(), [&systemConnector](auto& sys) { sys->connect(systemConnector); });

        // Initialise all systems
        std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->init(); });

    }

}
