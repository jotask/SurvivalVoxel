#include "system/mesh.hpp"

#include "system/chunk.hpp"
#include "system/chunk_system.hpp"
#include "system/camera_system.hpp"
#include "system/shader_system.hpp"
#include "system/vertex_info.hpp"
#include "engine.hpp"

#include <iostream>

namespace engine
{

    Mesh::Mesh(Chunk* parent, Shader& shader, const std::vector<VertexInfo> vertices, std::vector<unsigned int> indices)
        : m_chunk(parent)
        , m_vertices(vertices)
        , m_indices(indices)
        , m_shader(shader)
        , m_vao(0)
        , m_vbo(0)
        , m_ibo(0)
    {

    }

    Mesh::~Mesh()
    {
        destroy();
    }

    void Mesh::create()
    {

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        // Bind vbo
        glGenBuffers(1, &m_vbo);
        // Array Buffer Size for Vertices = Number of Vertices * size of each vertex 
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(VertexInfo), &m_vertices[0], GL_STATIC_DRAW);

        // Bind ibo
        glGenBuffers(1, &m_ibo);
        // Array Buffer Size for Indices = Number of Indices * size of each index (unsigned int)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(offsetof(VertexInfo, VertexInfo::m_position)));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(offsetof(VertexInfo, VertexInfo::m_normal)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(offsetof(VertexInfo, VertexInfo::m_color)));

        glBindVertexArray(0);

    }

    void Mesh::setTexture(const std::string & textureName, GLuint textureId)
    {
        if (textureId != 0)
        {
            m_textures[textureName] = textureId;
        }
        else
        {
            fprintf(stderr, "Failed to add new texture with name %s", textureName.c_str());
        }
    }

    GLuint Mesh::getTextureId(const std::string& texture) const
    {
        return m_textures.at(texture);
    }

    GLuint Mesh::getVao() const
    {
        return m_vao;
    }

    GLuint Mesh::getVbo() const
    {
        return m_vbo;
    }

    GLuint Mesh::getIbo() const
    {
        return m_ibo;
    }

    Shader& Mesh::getShader() const
    {
        return m_shader;
    }

    void Mesh::destroy()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ibo);
    }

    void Mesh::update()
    {

    }

    void Mesh::render()
    {
        auto* cameraSystem = Engine::getInstance().getSystem<CameraSystem>();
        m_shader.use();
        m_shader.setMat4("model_matrix", m_chunk->getTransform().getModelMatrix());
        m_shader.setMat4("view_matrix", cameraSystem->getViewMatrix());
        m_shader.setMat4("projection_matrix", cameraSystem->getProjectionMatrix());
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
    }

}

