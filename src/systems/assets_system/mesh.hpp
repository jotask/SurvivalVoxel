#pragma once

#include "systems/shader_system/shader.hpp"
#include "systems/assets_system/texture.hpp"

#include <vector>

#include "systems/shader_system/shader_attributes.hpp"
#include "systems/render_system/vertex_info.hpp"

namespace aiko
{

    class Mesh
    {
    public:

        Mesh(std::vector<VertexInfo> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
        ~Mesh() = default;

        void render(Shader& shader);

    private:

        GLuint VAO, VBO, EBO;
        std::vector<VertexInfo> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;

        void setupMesh();

    };

}
