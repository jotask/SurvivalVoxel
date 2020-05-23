#pragma once

#include "systems/chunk_system/voxel.hpp"
#include "systems/entity_component_system/components/component.hpp"
#include "systems/entity_component_system/components/mesh_component.hpp"
#include "utils/shared.hpp"

#include <glm/glm.hpp>

namespace engine
{

    class ChunkSystem;
    class Entity;

    class Chunk : public Component
    {
    public:

        static const glm::ivec3 s_chunkSize;

        Chunk(Entity* entity, const int x, const int z);

        void generate();

        Voxel& getVoxel(const glm::ivec3&);

        void updateModel();

    private:

        friend class Mesh;

        using VoxelId = unsigned int;

        unsigned int convertToVoxelIndex(const glm::ivec3&) const;

        std::map<VoxelId, Voxel> m_voxels;

        ChunkSystem* m_chunkSystem;

    };

}