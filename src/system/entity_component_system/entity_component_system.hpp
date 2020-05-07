#pragma once

#include "system/system_interface.hpp"
#include "system/entity_component_system/entity_types.hpp"

#include <vector>
#include <map>

namespace engine
{

    class Component;
    class Entity;
    class ImguiSystem;

    class EntityComponentSystem : public System
    {
    public:

        EntityComponentSystem();
        virtual ~EntityComponentSystem() override = default;

        virtual bool init() override;
        virtual bool connect(SystemConnector&) override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

        Entity& getEntityById(const entity::EntityId);
        Entity& getEntityByIdInTag(const entity::EntityId, const entity::EntityTag tag);

        entity::EntityCollection& getAllEntitiesByTag(const entity::EntityTag tag);

        void refresh();

        Entity& addEntity(const entity::EntityTag tag = entity::EntityTag::DEFAULT);

    private:

        std::map<entity::EntityTag, entity::EntityCollection> m_entities;

        ImguiSystem* m_imguiSystem;
        bool m_renderImgui;

    };

}
