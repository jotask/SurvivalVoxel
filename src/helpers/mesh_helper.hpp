#pragma once

#include "system/entity_component_system/components/mesh.hpp"
#include "system/shader_system/shader_system.hpp"
#include "system/chunk_system/vertex_info.hpp"
#include "system/chunk_system/chunk.hpp"
#include "system/shader_system/shader.hpp"
#include "utils/shared.hpp"
#include "engine.hpp"

#include <memory>
#include <random>

namespace engine
{

    namespace mesh
    {
        namespace helper
        {

            static glm::vec4 getVoxelColor(Voxel& voxel)
            {
                switch (voxel.getVoxelId())
                {
                    case VoxelInfo::VoxelId::DIRT:      return { 224 / 255.f, 204 / 255.f, 022 / 255.f, 1.f };
                    case VoxelInfo::VoxelId::GRASS:     return { 137 / 255.f, 023 / 255.f, 040 / 255.f, 1.f };
                    case VoxelInfo::VoxelId::BEDROCK:   return { 064 / 255.f, 064 / 255.f, 064 / 255.f, 1.f };
                    default: return {1.f, 1.f, 0.f, 1.f};
                }
            }

            static AikoUPtr<Mesh> generateChunkMesh(Chunk* chunk)
            {

                std::vector<VertexInfo> vertices;
                std::vector<unsigned int> indices;

                enum class Face { Front, Back, Top, Bottom, Left, Right};

                auto shouldMakeFace = [chunk](int x, int y, int z , Face face)
                {
                    switch (face)
                    {
                    case Face::Front:
                        return (z == Chunk::s_chunkSize.z - 1 || chunk->getVoxel({ x , y , z + 1 }).getVoxelType() == VoxelInfo::VoxelType::AIR);
                    case Face::Back:
                        return (z == 0 || chunk->getVoxel({ x , y , z - 1 }).getVoxelType() == VoxelInfo::VoxelType::AIR);
                    case Face::Top:
                        return (y == Chunk::s_chunkSize.y - 1 || chunk->getVoxel({ x , y + 1, z }).getVoxelType() == VoxelInfo::VoxelType::AIR);
                    case Face::Bottom:
                        return (y == 0 || chunk->getVoxel({ x , y - 1, z }).getVoxelType() == VoxelInfo::VoxelType::AIR);
                    case Face::Left:
                        return (x == 0 || chunk->getVoxel({ x - 1, y, z }).getVoxelType() == VoxelInfo::VoxelType::AIR);
                    case Face::Right:
                        return (x == Chunk::s_chunkSize.x - 1 || chunk->getVoxel({ x + 1, y, z }).getVoxelType() == VoxelInfo::VoxelType::AIR);
                    default:
                        return true;
                    }
                };

                std::random_device rd;
                std::mt19937 eng(rd());
                std::uniform_real_distribution<float> distr(0.f, 1.f);

                const auto size = glm::vec3(1.f);
                
                for (auto z = 0; z < Chunk::s_chunkSize.z; z++)
                {
                    for (auto x = 0; x < Chunk::s_chunkSize.x; x++)
                    {
                        for (auto y = 0; y < Chunk::s_chunkSize.y; y++)
                        {

                            //const auto color = glm::vec4{ distr(eng), distr(eng), distr(eng), 0.15f };
                            auto& voxel = chunk->getVoxel({ x, y, z });
                            const auto color = getVoxelColor(voxel);

                            if (voxel.getVoxelType() == VoxelInfo::VoxelType::AIR)
                            {
                                continue;
                            }

                            if(shouldMakeFace(x, y, z, Face::Back) == true)
                            {
                                // Back Face Vertices + Texture Coordinates
                                vertices.push_back(VertexInfo(glm::vec3(x           , y             , z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x + size.x  , y             , z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x + size.x  , y + size.y    , z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x           , y + size.y    , z), glm::vec4(color)));
                            }

                            if (shouldMakeFace(x, y, z, Face::Right) == true)
                            {
                                // Right Face Vertices + Texture Coordinates
                                vertices.push_back(VertexInfo(glm::vec3(x + size.x, y + size.y  , z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x + size.x, y + size.y  , z + size.z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x + size.x, y           , z + size.z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x + size.x, y           , z), glm::vec4(color)));
                            }
                            
                            if (shouldMakeFace(x, y, z, Face::Front) == true)
                            {
                                // Front Face Vertices + Texture Coordinates
                                vertices.push_back(VertexInfo(glm::vec3(x           , y             , z + size.z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x + size.x  , y             , z + size.z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x + size.x  , y + size.y    , z + size.z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x           , y + size.y    , z + size.z), glm::vec4(color)));
                            }

                            if (shouldMakeFace(x, y, z, Face::Left) == true)
                            {
                                // Left Face Vertices + Texture Coordinates
                                vertices.push_back(VertexInfo(glm::vec3(x, y            , z + size.z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x, y            , z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x, y + size.y   , z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x, y + size.y   , z + size.z), glm::vec4(color)));
                            }
                            
                            if (shouldMakeFace(x, y, z, Face::Top) == true)
                            {
                                // Top Face Vertices + Texture Coordinates
                                vertices.push_back(VertexInfo(glm::vec3(x + size.x  , y + size.y , z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x           , y + size.y , z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x           , y + size.y , z + size.z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x + size.x  , y + size.y , z + size.z), glm::vec4(color)));
                            }
                            
                            if (shouldMakeFace(x, y, z, Face::Bottom) == true)
                            {
                                // Bottom Face Vertices + Texture Coordinates
                                vertices.push_back(VertexInfo(glm::vec3(x           , y, z + size.z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x + size.x  , y, z + size.z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x + size.x  , y, z), glm::vec4(color)));
                                vertices.push_back(VertexInfo(glm::vec3(x           , y, z), glm::vec4(color)));
                            }
                        }
                    }
                }

                for (auto idx = 0 ; idx < vertices.size() ; idx +=4)
                {
                    auto v = vertices.at(idx);
                    indices.push_back(idx + 0);
                    indices.push_back(idx + 1);
                    indices.push_back(idx + 2);
                    indices.push_back(idx + 0);
                    indices.push_back(idx + 2);
                    indices.push_back(idx + 3);
                }

                for (auto idx = 0 ; idx < indices.size() ; idx += 3)
                {
                    auto v1 = vertices[indices[idx + 1]].m_position - vertices[indices[idx]].m_position;
                    auto v2 = vertices[indices[idx + 2]].m_position - vertices[indices[idx]].m_position;
                    auto faceNormal = glm::cross(v1, v2);
                    vertices[indices[idx + 0]].m_normal += faceNormal;
                    vertices[indices[idx + 1]].m_normal += faceNormal;
                    vertices[indices[idx + 2]].m_normal += faceNormal;
                }

                for (auto& vertex : vertices)
                {
                    vertex.m_normal = glm::normalize(vertex.m_normal);
                }

                
                auto* shaderSystem = engine::Engine::getInstance().getSystem<ShaderSystem>();
                auto& shader = shaderSystem->getShader("chunkShader");
                auto mesh = std::make_unique<Mesh>(chunk, shader, vertices, indices);
                mesh->create();

                return std::move(mesh);
            }
        }
    }

}

