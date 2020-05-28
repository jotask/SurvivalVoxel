#include "mesh_component.hpp"

#include "systems/entity_component_system/entity.hpp"
#include "systems/render_system/vertex_info.hpp"
#include "engine.hpp"

#include <imgui.h>

#include <iostream>

namespace aiko
{

    Mesh::Mesh(Entity* entity, Shader& shader, MeshData& meshData)
        : Component(entity)
        , m_meshData(meshData)
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
        glBufferData(GL_ARRAY_BUFFER, m_meshData.vertices.size() * sizeof(VertexInfo), &m_meshData.vertices[0], GL_STATIC_DRAW);

        // Bind ibo
        glGenBuffers(1, &m_ibo);
        // Array Buffer Size for Indices = Number of Indices * size of each index (unsigned int)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_meshData.indices.size() * sizeof(unsigned int), &m_meshData.indices[0], GL_STATIC_DRAW);

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

    Mesh::MeshData& Mesh::getMeshData()
    {
        return m_meshData;
    }

    void Mesh::update()
    {

    }

    void Mesh::render()
    {

        static Material m_material = { {1.f, 1.f, 1.f}, {0.1f, 0.1f, 0.1f}, {1.f, 1.f, 1.f}, {10.f} };

        ImGui::Begin("Material");
        ImGui::SliderFloat3("ambient", &m_material.ambient.x, 0.f, 1.f);
        ImGui::SliderFloat3("diffuse", &m_material.diffuse.x, 0.f, 1.f);
        ImGui::SliderFloat3("specular", &m_material.specular.x, 0.f, 1.f);
        ImGui::SliderFloat("shininess", &m_material.shininess, 0.f, 100.f);
        ImGui::End();

        m_shader.use();

        m_shader.setVec3("material.ambient", m_material.ambient);
        m_shader.setVec3("material.diffuse", m_material.diffuse);
        m_shader.setVec3("material.specular", m_material.specular);
        m_shader.setFloat("material.shininess", m_material.shininess);
        m_shader.setMat4("model", getEntity()->getTransform().getModelMatrix());
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_meshData.indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

    }

}

