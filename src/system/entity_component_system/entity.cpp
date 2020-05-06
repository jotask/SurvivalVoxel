#include "entity.hpp"

#include "system/entity_component_system/components/component.hpp"

#include <algorithm>

namespace engine
{
    Entity::Entity()
    {

    }

    void Entity::update()
    {
        std::for_each(m_components.begin(), m_components.end(), [](auto& component) { component->update(); });
    }

    void Entity::render()
    {
        std::for_each(m_components.begin(), m_components.end(), [](auto& component) { component->render(); });
    }

    bool Entity::isActive() const
    {
        return m_active;
    }

    void Entity::destroy()
    {
        m_active = false;
    }

}

