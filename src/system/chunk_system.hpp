#pragma once

#include "system/system_interface.hpp"

#include <vector>

namespace engine
{

    class RenderSystem;
    class CameraSystem;
    class Chunk;

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

        friend class Mesh;

        std::vector<Chunk> m_chunks;

        RenderSystem* m_renderSystem;
        CameraSystem* m_cameraSystem;

    };

}
