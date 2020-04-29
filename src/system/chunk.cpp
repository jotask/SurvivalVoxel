#include "chunk.hpp"

#include "system/mesh_helper.hpp"
#include "system/chunk_system.hpp"

namespace engine
{

    const glm::ivec3 Chunk::s_chunkSize = glm::ivec3( 6, 6, 6 );

    Chunk::Chunk(ChunkSystem* chunkSystem, const int x, const int z)
        : m_chunkSystem(chunkSystem)
        , m_mesh(nullptr)
        , m_transform({x * s_chunkSize.x, 0, z * s_chunkSize.z})
    {

    }

    void Chunk::generate()
    {
        static auto on = true;
        for (auto y = 0; y < s_chunkSize.y; y++)
        {
            for (auto x = 0; x < s_chunkSize.x; x++)
            {
                for (auto z = 0; z < s_chunkSize.z ; z++)
                {

                    auto voxelType = VoxelInfo::VoxelType::AIR;
                    auto voxelId = VoxelInfo::VoxelId::BEDROCK;

                    if (y == 0)
                    {
                        voxelType = VoxelInfo::VoxelType::SOLID;
                        voxelId = VoxelInfo::VoxelId::BEDROCK;
                    }
                    else
                    {
                        std::random_device rd;
                        std::mt19937 eng(rd());
                        std::uniform_real_distribution<float> distr(0.f, 1.f);
                        if (distr(eng) < .5f)
                        {
                            voxelType = VoxelInfo::VoxelType::SOLID;
                            voxelId = (distr(eng) < .5f) ? VoxelInfo::VoxelId::GRASS : VoxelInfo::VoxelId::DIRT;
                        }
                    }

                    auto voxel = Voxel(voxelType, voxelId);
                    auto id = convertToVoxelIndex({ x, y, z });
                    m_voxels.emplace(id, voxel);

                    on = !on;
                }
                on = !on;
            }
            on = !on;
        }

        if (m_mesh == nullptr)
        {
            m_mesh = mesh::helper::generateChunkMesh(this);
        }
    }

    Voxel & Chunk::getVoxel(const glm::ivec3 & location)
    {
        auto index = convertToVoxelIndex(location);
        return m_voxels.at(index);
    }

    void Chunk::updateModel()
    {

    }

    void Chunk::renderMesh()
    {
        if (m_mesh != nullptr)
        {
            m_mesh->m_chunk = this;
            m_mesh->render();
        }
    }

    Transform & Chunk::getTransform()
    {
        return m_transform;
    }

    unsigned int Chunk::convertToVoxelIndex(const glm::ivec3& pos) const
    {
        return pos.x + s_chunkSize.x * (pos.y + s_chunkSize.z * pos.z);
    }

}