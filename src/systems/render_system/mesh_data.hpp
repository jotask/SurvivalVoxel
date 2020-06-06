#pragma once

#include "systems/render_system/vertex_info.hpp"
#include "systems/assets_system/texture.hpp"

#include <vector>

namespace aiko
{
    struct MeshData
    {
    public:

        MeshData(std::vector<VertexInfo> vertices, std::vector<GLuint> indices)
            : m_vertices(vertices)
            , m_indices(indices)
        {

        }

        ~MeshData() = default;

    // private:

        std::vector<VertexInfo> m_vertices;
        std::vector<GLuint> m_indices;
        std::vector<Texture> m_textures;
    };
}