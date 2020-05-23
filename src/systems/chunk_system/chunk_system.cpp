#include "chunk_system.hpp"

#include "systems/chunk_system/chunk.hpp"
#include "systems/entity_component_system/entity_component_system.hpp"
#include "systems/entity_component_system/entity.hpp"

#include <imgui.h>

#include <algorithm>

namespace aiko
{

    ChunkSystem::ChunkSystem()
        : m_entitySystem(nullptr)
    {

    }

    ChunkSystem::~ChunkSystem()
    {

    }

    bool ChunkSystem::init()
    {
        constexpr auto size = 2;
        for (auto z = -size; z < size; z++)
        {
            for (auto x = -size; x < size; x++)
            {
                auto& entity = m_entitySystem->addEntity(entity::EntityTag::CHUNK);
                auto& chunk = entity.addComponent<Chunk>(&entity, x, z);
                chunk.generate();
                m_chunks.push_back(entity.getId());
            }
        }
        return true;
    }

    bool ChunkSystem::connect(SystemConnector & connector)
    {
        m_entitySystem = connector.findSystem<EntityComponentSystem>();
        return true;
    }

    void ChunkSystem::preUpdate()
    {

    }

    void ChunkSystem::update()
    {

    }

    void ChunkSystem::postUpdate()
    {

    }

    void ChunkSystem::preRender()
    {

    }

    void ChunkSystem::render()
    {

    }

    void ChunkSystem::postRender()
    {

    }

}
