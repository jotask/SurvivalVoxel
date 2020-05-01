#include "chunk.hpp"

#include "system/mesh_helper.hpp"
#include "system/chunk_system.hpp"
#include "utils/utilities.hpp"

#include "PerlinNoise.hpp"

namespace engine
{

    const glm::ivec3 Chunk::s_chunkSize = glm::ivec3( 16, 16, 16 );

    Chunk::Chunk(ChunkSystem* chunkSystem, const int x, const int z)
        : m_chunkSystem(chunkSystem)
        , m_mesh(nullptr)
        , m_transform({x * s_chunkSize.x, 0, z * s_chunkSize.z})
    {

    }

    void Chunk::generate()
    {
        for (auto z = 0; z < s_chunkSize.z ; z++)
        {
            for (auto x = 0; x < s_chunkSize.x; x++)
            {

                const std::uint32_t seed = 1234;
                const std::uint32_t octaves = 1;
                const double frequency = 1.0;

                auto noise = siv::PerlinNoise(seed);

                const auto fx = s_chunkSize.x / frequency;
                const auto fz = s_chunkSize.z / frequency;

                const auto terrainLevel = noise.accumulatedOctaveNoise2D_0_1((x + m_transform.position.x) / fx, (z + m_transform.position.z) / fz, octaves);
                const auto groundLevel = utils::map(terrainLevel, 0.0, 1.0, 0.0, static_cast<double>(s_chunkSize.y));

                for (auto y = 0; y < s_chunkSize.y; y++)
                {

                    auto voxelType = VoxelInfo::VoxelType::AIR;
                    auto voxelId = VoxelInfo::VoxelId::BEDROCK;

                    if (y <= groundLevel)
                    {
                        voxelType = VoxelInfo::VoxelType::SOLID;
                        if (y == 0)
                        {
                            voxelId = VoxelInfo::VoxelId::BEDROCK;
                        }
                        else
                        {
                            std::random_device rd;
                            std::mt19937 eng(rd());
                            std::uniform_real_distribution<float> distr(0.f, 1.f);
                            voxelId = (distr(eng) < .5f) ? VoxelInfo::VoxelId::GRASS : VoxelInfo::VoxelId::DIRT;
                        }
                    }

                    auto voxel = Voxel(voxelType, voxelId);
                    auto id = convertToVoxelIndex({ x, y, z });
                    m_voxels.emplace(id, voxel);
                }
            }
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

    Mesh* Chunk::getMesh() const
    {
        return m_mesh.get();
    }

    unsigned int Chunk::convertToVoxelIndex(const glm::ivec3& pos) const
    {
        return pos.x + s_chunkSize.x * (pos.y + s_chunkSize.z * pos.z);
    }

}