#pragma once

#include "utils/shared.hpp"
#include "systems/event_system/event.hpp"
#include "systems/system_interface.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace aiko
{

    class DisplaySystem;

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

        DisplaySystem*   m_displaySystem;

        bool m_shouldBeRunning;

    };

}

