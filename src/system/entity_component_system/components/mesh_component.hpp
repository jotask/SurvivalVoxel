#pragma once

#include "system/chunk_system/vertex_info.hpp"
#include "system/shader_system/shader.hpp"
#include "system/render_system/material.hpp"
#include "system/entity_component_system/components/component.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <map>

namespace engine
{

    class Mesh : public Component
    {

    public:

        Mesh(Shader& shader, const std::vector<VertexInfo> vertices, std::vector<unsigned int> indices);
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

    private:

        Shader& m_shader;
        GLuint m_vao;
        GLuint m_vbo;
        GLuint m_ibo;
        std::map<std::string, GLuint> m_textures;
        std::vector<VertexInfo> m_vertices;
        std::vector<unsigned int> m_indices;
    };
}
