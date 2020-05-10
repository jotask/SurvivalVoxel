#pragma once

#include "system/entity_component_system/components/mesh_component.hpp"
#include "system/chunk_system/vertex_info.hpp"
#include "engine.hpp"
#include "system/shader_system/shader_system.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <algorithm>

namespace engine
{

    namespace factory
    {
        namespace mesh
        {

            static Mesh::MeshData generateSpehereData(const int _resolution, const float _radius)
            {

                const auto res = std::max(_resolution, 20);

                const auto stacks = res;
                const auto slices = res;
                const auto radius = _radius;

                std::vector<VertexInfo> vertices;
                std::vector<unsigned int> indices;

                // Calc The Vertices
                for (int i = 0; i <= stacks; ++i) {

                    float V = i / static_cast<float>(stacks);
                    float phi = V * glm::pi<float>();

                    // Loop Through Slices
                    for (int j = 0; j <= slices; ++j) {

                        float U = j / static_cast<float>(slices);
                        float theta = U * (glm::pi <float>() * 2);

                        // Calc The Vertex Positions
                        float x = cosf(theta) * sinf(phi);
                        float y = cosf(phi);
                        float z = sinf(theta) * sinf(phi);

                        // Push Back Vertex Data
                        vertices.push_back({ (glm::vec3(x, y, z) * radius), glm::vec4(1.f, 0.f, 0.f, 1.f) });
                    }
                }

                // Calc The Index Positions
                for (int i = 0; i < slices * stacks + slices; ++i) {

                    indices.push_back(i);
                    indices.push_back(i + slices + 1);
                    indices.push_back(i + slices);

                    indices.push_back(i + slices + 1);
                    indices.push_back(i);
                    indices.push_back(i + 1);
                }

                // Calculate normals
                for (auto idx = 0; idx < indices.size(); idx += 3)
                {
                    auto v1 = vertices[indices[idx + 1]].m_position - vertices[indices[idx]].m_position;
                    auto v2 = vertices[indices[idx + 2]].m_position - vertices[indices[idx]].m_position;
                    auto faceNormal = glm::cross(v1, v2);
                    vertices[indices[idx + 0]].m_normal += faceNormal;
                    vertices[indices[idx + 1]].m_normal += faceNormal;
                    vertices[indices[idx + 2]].m_normal += faceNormal;
                }

                // normalize normals
                for (auto& vertex : vertices)
                {
                    vertex.m_normal = glm::normalize(vertex.m_normal);
                }

                return {vertices, indices};
            }

        }
    }

}
