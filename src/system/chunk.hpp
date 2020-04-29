#pragma once

#include "system/voxel.hpp"
#include "system/mesh.hpp"
#include "utils/shared.hpp"

#include "transform.hpp"

#include <glm/glm.hpp>

namespace engine
{

    class ChunkSystem;

    class Chunk
    {
    public:

        static const glm::ivec3 s_chunkSize;

        Chunk(ChunkSystem* chunkSystem, const int x, const int z);

        void generate();

        Voxel& getVoxel(const glm::ivec3&);

        void updateModel();

        void renderMesh();

        Transform& getTransform();

    private:

        friend class Mesh;

        using VoxelId = unsigned int;

        unsigned int convertToVoxelIndex(const glm::ivec3&) const;

        std::map<VoxelId, Voxel> m_voxels;

        ChunkSystem* m_chunkSystem;

        AikoUPtr<Mesh> m_mesh;

        Transform m_transform;

    };

}