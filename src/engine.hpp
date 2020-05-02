#pragma once

#include "utils/shared.hpp"
#include "system/event.hpp"
#include "system/system_interface.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace engine
{

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

        void onWindowClosing(Event&);

    public:
        ~Engine() = default;

        void run();

        // TODO : Find better design for free dependency
        template<class T>
        T* getSystem()
        {
            for (auto& m : m_systems)
            {
                if (T* tmp = dynamic_cast<T*>(m.get())) {
                    return tmp;
                }
            }
            return nullptr;
        }

    private:

        void init();

        std::vector<AikoUPtr<System>> m_systems;

        RenderSystem*   m_renderSystem;

        bool m_shouldBeRunning;

    };

}

