#pragma once

#include "system/system_interface.hpp"
#include "system/entity_component_system/entity_types.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace engine
{

    class EntityComponentSystem;
    class Entity;

    class ChunkSystem : public System
    {
    public:

        ChunkSystem();
        virtual ~ChunkSystem() override;

        virtual bool init() override;
        virtual bool connect(SystemConnector&) override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

    private:

        std::vector<entity::EntityId> m_chunks;

        EntityComponentSystem* m_entitySystem;

    };

}
