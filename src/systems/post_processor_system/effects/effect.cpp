#include "effect.hpp"

namespace aiko
{
    namespace postprocessing
    {

        Effect::Effect(const std::string& name)
            : m_name(name)
            , m_enabled(false)
        {

        }

        const std::string& Effect::getName() const
        {
            return m_name;
        }

        bool & Effect::isEnabled()
        {
            return m_enabled;
        }

    }
}
