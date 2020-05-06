#include "entity_component_system.hpp"

#include "system/imgui_system.hpp"
#include "system/entity_component_system/entity.hpp"
#include "system/entity_component_system/components/component.hpp"
#include "utils/shared.hpp"

#include <imgui.h>

#include <algorithm>

namespace engine
{
    EntityComponentSystem::EntityComponentSystem()
        : m_renderImgui(false)
    {

    }

    bool EntityComponentSystem::connect(SystemConnector & connector)
    {
        m_imguiSystem = connector.findSystem< ImguiSystem>();
        return true;
    }

    bool EntityComponentSystem::init()
    {
        m_imguiSystem->registerSystem("EntityComponentSystem", m_renderImgui);
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

        if (m_renderImgui == true)
        {
            ImGui::Begin("EntityComponentSystem", &m_renderImgui);
            ImGui::Text("N. entities: %i", static_cast<int>(m_entities.size()));
            ImGui::End();
        }

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
