#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "utils/shared.hpp"
#include "system/system_interface.hpp"

namespace engine
{

    class DisplaySystem;
    class RenderSystem;

    class Engine
    {
    public:
        static Engine& getInstance()
        {
            static Engine instance;
            return instance;
        }
        Engine(Engine const&) = delete;
        void operator=(Engine const&) = delete;
    private:

        Engine();

    public:
        ~Engine() = default;

        void run();

    private:

        void init();

        std::vector<AikoUPtr<System>> m_systems;

        DisplaySystem*  m_displaySystem;
        RenderSystem*   m_renderSystem;

    };

}

