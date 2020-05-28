#pragma once

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

    class Mesh
    {
    public:

        /*  Mesh Data  */
        std::vector<VertexInfo> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;

        /*  Functions  */
        // Constructor
        Mesh(std::vector<VertexInfo> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
        {
            this->vertices = vertices;
            this->indices = indices;
            this->textures = textures;

            // Now that we have all the required data, set the vertex buffers and its attribute pointers.
            this->setupMesh();
        }

        // Render the mesh
        void render(Shader& shader)
        {
            // Bind appropriate textures
            GLuint diffuseNr = 1;
            GLuint specularNr = 1;

            for (GLuint i = 0; i < this->textures.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
                // Retrieve texture number (the N in diffuse_textureN)
                std::stringstream ss;
                std::string number;
                std::string name = this->textures[i].getType();

                if (name == "texture_diffuse")
                {
                    ss << diffuseNr++; // Transfer GLuint to stream
                }
                else if (name == "texture_specular")
                {
                    ss << specularNr++; // Transfer GLuint to stream
                }

                number = ss.str();
                // Now set the sampler to the correct texture unit
                const auto uniformLocation = glGetUniformLocation(shader.getProgramId(), (name + '_' + number).c_str());

                if (uniformLocation == -1)
                {
                    std::cout << "Uniform location not found for " << (name + '_' + number).c_str() << std::endl;
                    throw std::runtime_error("Uniform location not found for " + (name + '_' + number));
                }

                glUniform1i(uniformLocation, i);
                // And finally bind the texture
                glBindTexture(GL_TEXTURE_2D, this->textures[i].getId());
            }

            // Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
            glUniform1f(glGetUniformLocation(shader.getProgramId(), "material.shininess"), 16.0f);

            // Draw mesh
            glBindVertexArray(this->VAO);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->indices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            // Always good practice to set everything back to defaults once configured.
            for (GLuint i = 0; i < this->textures.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }

    private:
        /*  Render data  */
        GLuint VAO, VBO, EBO;

        /*  Functions    */
        // Initializes all the buffer objects/arrays
        void setupMesh()
        {
            // Create buffers/arrays
            glGenVertexArrays(1, &this->VAO);
            glBindVertexArray(this->VAO);


            // Load data into vertex buffers
            glGenBuffers(1, &this->VBO);
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(VertexInfo), &this->vertices[0], GL_STATIC_DRAW);

            glGenBuffers(1, &this->EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

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
        }

    };

}
