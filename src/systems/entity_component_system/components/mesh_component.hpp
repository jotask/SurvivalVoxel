#pragma once

#include "systems/render_system/vertex_info.hpp"
#include "systems/shader_system/shader.hpp"
#include "systems/render_system/material.hpp"
#include "systems/entity_component_system/components/component.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <map>

namespace aiko
{

    class Entity;

    class Mesh : public Component
    {
    public:

        struct MeshData
        {
            MeshData(const std::vector<VertexInfo> _vertices, std::vector<unsigned int> _indices)
                : vertices(_vertices)
                , indices(_indices)
            {

            }
            const std::vector<VertexInfo> vertices;
            std::vector<unsigned int> indices;
        };

        Mesh(Entity* entity, Shader& shader, MeshData& meshData);
        ~Mesh();

        void create();

        void setTexture(const std::string& textureName, GLuint textureId);
        GLuint getTextureId(const std::string& texture) const;
        GLuint getVao() const;
        GLuint getVbo() const;
        GLuint getIbo() const;
        Shader& getShader() const;

        void update();
        void render();
        void destroy();

        MeshData& getMeshData();

    private:

        MeshData m_meshData;
        Shader& m_shader;
        GLuint m_vao;
        GLuint m_vbo;
        GLuint m_ibo;
        std::map<std::string, GLuint> m_textures;

    };
}
