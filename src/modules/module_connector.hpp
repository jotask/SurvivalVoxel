#pragma once

#include <vector>

#include "utils/shared.hpp"

namespace aiko
{

    class Module;

    class ModuleConnector
    {
    public:

        using Modules = std::vector<AikoUPtr<Module>>;

        ModuleConnector(Modules& systems)
            : m_systems(systems)
        {

        }

        template <class T>
        T* findModule()
        {
            for (auto& m : m_modules)
            {
                if (T* tmp = dynamic_cast<T*>(m.get())) {
                    return tmp;
                }
            }
            return nullptr;
        }

    private:

        Modules& m_systems;

    };

}
