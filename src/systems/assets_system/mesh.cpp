#include "mesh.hpp"

#include "systems/shader_system/shader.hpp"
#include "systems/assets_system/texture.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "systems/shader_system/shader_attributes.hpp"
#include "systems/render_system/vertex_info.hpp"

namespace aiko
{

    Mesh::Mesh(const MeshData& data)
        : Asset(AssetType::Mesh)
        , m_meshData(data)
    {
        load();
    }

    // Render the mesh
    void Mesh::render(Shader& shader)
    {

        shader.use();

        // Bind appropriate textures
        GLuint diffuseNr = 1;
        GLuint specularNr = 1;
        GLuint normalNr = 1;
        GLuint heightNr = 1;

        for (GLuint i = 0; i < m_meshData.m_textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = m_meshData.m_textures[i].getType();
            if (name == "texture_diffuse")
            {
                number = std::to_string(diffuseNr++);
            }
            else if (name == "texture_specular")
            {
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            }
            else if (name == "texture_normal")
            {
                number = std::to_string(normalNr++); // transfer unsigned int to stream
            }
            else if (name == "texture_height")
            {
                number = std::to_string(heightNr++); // transfer unsigned int to stream
            }

            // Now set the sampler to the correct texture unit
            shader.setInt((name + '_' + number).c_str(), i);

            // And finally bind the texture
            glBindTexture(GL_TEXTURE_2D, m_meshData.m_textures[i].getId());
        }

        // Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
        // glUniform1f(glGetUniformLocation(shader.getProgramId(), "material.shininess"), 16.0f);

        // Draw mesh
        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_meshData.m_indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Always good practice to set everything back to defaults once configured.
        for (GLuint i = 0; i < m_meshData.m_textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        shader.unuse();

    }

    bool Mesh::load()
    {
        // Create buffers/arrays
        glGenVertexArrays(1, &this->VAO);
        glBindVertexArray(this->VAO);

        // Load data into vertex buffers
        glGenBuffers(1, &this->VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, m_meshData.m_vertices.size() * sizeof(VertexInfo), &m_meshData.m_vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &this->EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_meshData.m_indices.size() * sizeof(GLuint), &m_meshData.m_indices[0], GL_STATIC_DRAW);

        // Set the vertex attribute pointers
        // Vertex Positions
        glEnableVertexAttribArray(GLuint(Attributes::Position));
        glVertexAttribPointer(GLuint(Attributes::Position), 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (GLvoid *)offsetof(VertexInfo, m_position));
        // Vertex Normals
        glEnableVertexAttribArray(GLuint(Attributes::Normal));
        glVertexAttribPointer(GLuint(Attributes::Normal), 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (GLvoid *)offsetof(VertexInfo, m_normal));
        // Vertex Color
        glEnableVertexAttribArray(GLuint(Attributes::Color));
        glVertexAttribPointer(GLuint(Attributes::Color), 4, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (GLvoid *)offsetof(VertexInfo, m_color));
        // Vertex Texture Coords
        glEnableVertexAttribArray(GLuint(Attributes::UVs));
        glVertexAttribPointer(GLuint(Attributes::UVs), 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (GLvoid *)offsetof(VertexInfo, m_texture));

        glBindVertexArray(0);

        return true;

    }

}
