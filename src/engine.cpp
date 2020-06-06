#include "engine.hpp"

#include "systems/display_system.hpp"
#include "systems/debug_system.hpp"
#include "systems/render_system/render_system.hpp"
#include "systems/imgui_system.hpp"
#include "systems/input_system.hpp"
#include "systems/camera_system.hpp"
#include "systems/assets_system/assets_system.hpp"
#include "systems/shader_system/shader_system.hpp"
#include "systems/audio_system/audio_system.hpp"
#include "systems/light_system/light_system.hpp"
#include "systems/physics_system/physics_system.hpp"
#include "systems/event_system/event_system.hpp"
#include "systems/system_connector.hpp"
#include "systems/entity_component_system/entity_component_system.hpp"
#include "systems/event_system/engine_events.hpp"
#include "systems/game_state_manager_system/game_state_manager_system.hpp"

#include "systems/chunk_system/chunk_system.hpp"

#include <algorithm>

namespace aiko
{
    Engine::Engine()
        : m_renderSystem(nullptr)
        , m_shouldBeRunning(true)
    {

    }

    void Engine::onWindowClosing(Event & evnt)
    {
        m_shouldBeRunning = false;
    }

    void Engine::init()
    {

        EventSystem::it().bind<WindowCloseEvent>(this, &Engine::onWindowClosing);

        // Create all systems first
        // Engine systems first
        m_systems.push_back(std::make_unique<DisplaySystem>());
        m_systems.push_back(std::make_unique<RenderSystem>());
        m_systems.push_back(std::make_unique<DebugSystem>());
        m_systems.push_back(std::make_unique<ImguiSystem>());
        m_systems.push_back(std::make_unique<InputSystem>());
        m_systems.push_back(std::make_unique<CameraSystem>());
        m_systems.push_back(std::make_unique<ShaderSystem>());
        m_systems.push_back(std::make_unique<LightSystem>());
        m_systems.push_back(std::make_unique<PhysicsSystem>());
        m_systems.push_back(std::make_unique<AudioSystem>());
        m_systems.push_back(std::make_unique<EntityComponentSystem>());
        m_systems.push_back(std::make_unique<AssetsSystem>());
        m_systems.push_back(std::make_unique<GameStateManagerSystem>());

        // Game systems
        // m_systems.push_back(std::make_unique<ChunkSystem>());

        // Connect all system before we initialize them
        auto systemConnector = SystemConnector(m_systems);
        m_renderSystem = systemConnector.findSystem<RenderSystem>();
        std::for_each(m_systems.begin(), m_systems.end(), [&systemConnector](auto& sys) { sys->connect(systemConnector); });

        // Initialise all systems
        std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->init(); });

    }

    void Engine::run()
    {

        init();

        while (m_shouldBeRunning == true)
        {

            // Update all systems
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->preUpdate(); });
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->update(); });
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->postUpdate(); });

            // Render all systems
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->beginFrame(); });
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->preRender(); });
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->render(); });
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->postRender(); });
            std::for_each(m_systems.begin(), m_systems.end(), [](auto& sys) { sys->endFrame(); });

            m_renderSystem->swapBuffers();

        }

    }

}
