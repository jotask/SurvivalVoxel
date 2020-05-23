#include "chunk.hpp"

#include "systems/chunk_system/chunk_factory.hpp"
#include "systems/entity_component_system/entity.hpp"
#include "systems/chunk_system/chunk_system.hpp"
#include "utils/utilities.hpp"

#include "PerlinNoise.hpp"

namespace aiko
{

    const glm::ivec3 Chunk::s_chunkSize = glm::ivec3( 16, 16, 16 );

    Chunk::Chunk(Entity* entity, const int x, const int z)
        : Component(entity)
    {
        getEntity()->getTransform().position = { x * s_chunkSize.x, 0, z * s_chunkSize.z };
    }

    void Chunk::generate()
    {
        const auto& transform = getEntity()->getTransform();
        for (auto z = 0; z < s_chunkSize.z ; z++)
        {
            for (auto x = 0; x < s_chunkSize.x; x++)
            {

                const std::uint32_t seed = 1234;
                const std::uint32_t octaves = 1;
                const double frequency = 1.0;

                const auto amplitude = 2.f;

                auto noise = siv::PerlinNoise(seed);

                const auto fx = (s_chunkSize.x / frequency) * amplitude;
                const auto fy = (s_chunkSize.y / frequency) * amplitude;
                const auto fz = (s_chunkSize.z / frequency) * amplitude;

                const auto terrainLevel = noise.accumulatedOctaveNoise2D_0_1((x + transform.position.x) / fx, (z + transform.position.z) / fz, octaves);
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
                            const auto blockX = (x + transform.position.x) / (fx * 0.25f);
                            const auto blockY = (y + transform.position.y) / (fy * 0.25f);
                            const auto blockZ = (z + transform.position.z) / (fz * 0.25f);
                            const auto blockType = noise.noise3D_0_1(blockX, blockY, blockZ);

                            voxelId = (blockType < .5f) ? VoxelInfo::VoxelId::GRASS : VoxelInfo::VoxelId::DIRT;
                        }
                    }

                    auto voxel = Voxel(voxelType, voxelId);
                    auto id = convertToVoxelIndex({ x, y, z });
                    m_voxels.emplace(id, voxel);
                }
            }
        }
        
        if (getEntity()->hasComponent<Mesh>() == false)
        {

            auto* shaderSystem = aiko::Engine::getInstance().getSystem<ShaderSystem>();
            auto& shader = shaderSystem->getShader("chunkShader");


            auto data = chunk::factory::generateChunkData(this);
            auto* entity = getEntity();
            auto& mesh = getEntity()->addComponent<Mesh>(entity, shader, data);
            mesh.create();
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

    unsigned int Chunk::convertToVoxelIndex(const glm::ivec3& pos) const
    {
        return pos.x + s_chunkSize.x * (pos.y + s_chunkSize.z * pos.z);
    }

}