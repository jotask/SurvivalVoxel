#include "engine.hpp"

#include "system/display_system.hpp"
#include "system/render_system.hpp"
#include "system/imgui_system.hpp"
#include "system/input_system.hpp"
#include "system/camera_system.hpp"
#include "system/model_system.hpp"
#include "system/shader_system.hpp"
#include "system/light_system.hpp"
#include "system/event_system.hpp"
#include "system/system_connector.hpp"

#include "system/chunk_system.hpp"

#include <algorithm>

namespace engine
{
    Engine::Engine()
        : m_displaySystem(nullptr)
        , m_renderSystem(nullptr)
    {

    }

    void Engine::init()
    {

        // Create all systems first
        // Engine systems first
        m_systems.push_back(std::make_unique<DisplaySystem>());
        m_systems.push_back(std::make_unique<RenderSystem>());
        m_systems.push_back(std::make_unique<ImguiSystem>());
        m_systems.push_back(std::make_unique<InputSystem>());
        m_systems.push_back(std::make_unique<CameraSystem>());
        m_systems.push_back(std::make_unique<ShaderSystem>());
        m_systems.push_back(std::make_unique<LightSystem>());
        m_systems.push_back(std::make_unique<ModelSystem>());

        // Game systems
        m_systems.push_back(std::make_unique<ChunkSystem>());

        // Connect all system before we initialize them
        auto systemConnector = SystemConnector(m_systems);
        m_displaySystem = systemConnector.findSystem<DisplaySystem>();
        m_renderSystem = systemConnector.findSystem<RenderSystem>();
        std::for_each(m_systems.begin(), m_systems.end(), [&systemConnector](auto& sys) { sys->connect(systemConnector); });

        // Initialise all systems
        std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->init(); });

    }

    void Engine::run()
    {

        init();

        double previousTime = glfwGetTime();
        int frameCount = 0;

        while (m_displaySystem->shouldWindowClose() == false)
        {
            // FPS calculations :: TODO Improve this
            {
                double currentTime = glfwGetTime();
                frameCount++;
                if (currentTime - previousTime >= 1.0)
                {
                    auto fps = static_cast<double>(frameCount) / ( currentTime - previousTime );
                    previousTime = currentTime;
                    frameCount = 0;
                    std::cout << fps << std::endl;
                }
            }

            // Update all systems
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->preUpdate(); });
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->update(); });
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->postUpdate(); });

            // Render all systems
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->preRender(); });
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->render(); });
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->postRender(); });

            m_renderSystem->swapBuffers();

        }

    }

}
