#pragma once

#include <vector>

#include "utils/shared.hpp"

namespace engine
{

    class System;

    class SystemConnector
    {
    public:

        using Systems = std::vector<AikoUPtr<System>>;

        SystemConnector(Systems& systems)
            : m_systems(systems)
        {

        }

        template <class T>
        T* findSystem()
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

        Systems& m_systems;

    };

}
