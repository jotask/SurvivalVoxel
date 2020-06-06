#pragma once

#include "systems/shader_system/shader.hpp"
#include "systems/render_system/mesh_data.hpp"
#include "systems/assets_system/texture.hpp"
#include "systems/assets_system/asset.hpp"
#include "systems/shader_system/shader_attributes.hpp"
#include "systems/render_system/vertex_info.hpp"

#include <vector>

namespace aiko
{

    class Mesh : public Asset
    {
    public:

        Mesh(const MeshData& data);
        virtual ~Mesh() = default;

        virtual bool load();

        void render(Shader& shader);

    private:

        GLuint VAO, VBO, EBO;

        MeshData m_meshData;

    };

}
