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

        DisplaySystem*  m_displaySystem;
        RenderSystem*   m_renderSystem;

    };

}

