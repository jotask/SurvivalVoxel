#include "entity_component_system.hpp"

#include "system/entity_component_system/entity.hpp"
#include "system/entity_component_system/components/component.hpp"
#include "utils/shared.hpp"

#include <algorithm>

namespace engine
{
    EntityComponentSystem::EntityComponentSystem()
    {

    }

    bool EntityComponentSystem::init()
    {
        return true;
    }

    bool EntityComponentSystem::connect(SystemConnector & connector)
    {
        return true;
    }

    void EntityComponentSystem::preUpdate()
    {

    }

    void EntityComponentSystem::update()
    {
        std::for_each(m_entities.begin(), m_entities.end(), [](auto& entity) { entity->update(); });
    }

    void EntityComponentSystem::postUpdate()
    {

    }

    void EntityComponentSystem::preRender()
    {

    }

    void EntityComponentSystem::render()
    {
        std::for_each(m_entities.begin(), m_entities.end(), [](auto& entity) { entity->render(); });
    }

    void EntityComponentSystem::postRender()
    {

    }

    void EntityComponentSystem::refresh()
    {
        m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [](const auto& entity) { return entity->isActive() == false; }));

    }

    Entity& EntityComponentSystem::addEntity()
    {
        Entity* e = new Entity();
        AikoUPtr<Entity> ptr{ e };
        m_entities.emplace_back(std::move(ptr));
        return *e;
    }

}
