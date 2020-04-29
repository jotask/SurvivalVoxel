#include "system/chunk_system.hpp"

#include "system/render_system.hpp"
#include "system/camera_system.hpp"
#include "system/chunk.hpp"

#include <algorithm>

namespace engine
{

    ChunkSystem::ChunkSystem()
        : m_renderSystem(nullptr)
        , m_cameraSystem(nullptr)
    {

    }

    ChunkSystem::~ChunkSystem()
    {

    }

    bool ChunkSystem::init()
    {
        constexpr auto size = 2u;
        for (auto z = 0; z < size; z++)
        {
            for (auto x = 0; x < size; x++)
            {
                 auto chunk = Chunk(this, x, z);
                 chunk.generate();
                 m_chunks.push_back(std::move(chunk));
            }
        }
        return true;
    }

    bool ChunkSystem::connect(SystemConnector & connector)
    {
        m_renderSystem = connector.findSystem<RenderSystem>();
        m_cameraSystem = connector.findSystem<CameraSystem>();
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
        for (auto& chunk : m_chunks)
        {
            chunk.renderMesh();
        }
    }

    void ChunkSystem::postRender()
    {

    }

}
