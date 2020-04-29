#include "system/model.hpp"

#include "system/vertex_info.hpp"

#define PI 3.14159265

namespace engine
{

    namespace model
    {

        Model::Model()
        {

        }

        Model::~Model()
        {
            destroy();
        }

        void Model::create()
        {
            GLuint vao;
            GLuint vbo;
            GLuint ibo;

            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            std::vector<VertexInfo> vertices;
            std::vector<unsigned int> indices = {
                // Front Face
                0, 1, 2, 0, 2, 3,
                // Right Face
                4, 5, 6, 4, 6, 7,
                // Back Face
                8, 9, 10, 8, 10, 11,
                // Left Face
                12, 13, 14, 12, 14, 15,
                // Top Face
                16, 17, 18, 16, 18, 19,
                // Bottom Face
                20, 21, 22, 20, 22, 23 };

            // Front Face Vertices + Texture Coordinates
            // vertices.push_back(VertexInfo(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(0, 0)));
            // vertices.push_back(VertexInfo(glm::vec3(1.0, -1.0, 1.0), glm::vec2(1, 0)));
            // vertices.push_back(VertexInfo(glm::vec3(1.0, 1.0, 1.0), glm::vec2(1, 1)));
            // vertices.push_back(VertexInfo(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(0, 1)));
            // 
            // // Right Face Vertices + Texture Coordinates
            // vertices.push_back(VertexInfo(glm::vec3(1.0, 1.0, 1.0), glm::vec2(0, 0)));
            // vertices.push_back(VertexInfo(glm::vec3(1.0, 1.0, -1.0), glm::vec2(1, 0)));
            // vertices.push_back(VertexInfo(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 1)));
            // vertices.push_back(VertexInfo(glm::vec3(1.0, -1.0, 1.0), glm::vec2(0, 1)));
            // 
            // // Back Face Vertices + Texture Coordinates
            // vertices.push_back(VertexInfo(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
            // vertices.push_back(VertexInfo(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 0)));
            // vertices.push_back(VertexInfo(glm::vec3(1.0, 1.0, -1.0), glm::vec2(1, 1)));
            // vertices.push_back(VertexInfo(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(0, 1)));
            // 
            // // Left Face Vertices + Texture Coordinates
            // vertices.push_back(VertexInfo(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
            // vertices.push_back(VertexInfo(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(1, 0)));
            // vertices.push_back(VertexInfo(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(1, 1)));
            // vertices.push_back(VertexInfo(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(0, 1)));
            // 
            // // Top Face Vertices + Texture Coordinates
            // vertices.push_back(VertexInfo(glm::vec3(1.0, 1.0, 1.0), glm::vec2(0, 0)));
            // vertices.push_back(VertexInfo(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(1, 0)));
            // vertices.push_back(VertexInfo(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(1, 1)));
            // vertices.push_back(VertexInfo(glm::vec3(1.0, 1.0, -1.0), glm::vec2(0, 1)));
            // 
            // // Bottom Face Vertices + Texture Coordinates
            // vertices.push_back(VertexInfo(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
            // vertices.push_back(VertexInfo(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 0)));
            // vertices.push_back(VertexInfo(glm::vec3(1.0, -1.0, 1.0), glm::vec2(1, 1)));
            // vertices.push_back(VertexInfo(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(0, 1)));

            // Bind vbo
            glGenBuffers(1, &vbo);
            // Array Buffer Size for Vertices = Number of Vertices * size of each vertex 
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexInfo), &vertices[0], GL_STATIC_DRAW);

            // Bind ibo
            glGenBuffers(1, &ibo);
            // Array Buffer Size for Indices = Number of Indices * size of each index (unsigned int)
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(offsetof(VertexInfo, VertexInfo::m_texture)));
            glBindVertexArray(0);
            m_vao = vao;
            m_vbos.push_back(vbo);
            m_vbos.push_back(ibo);

            rotation_speed = glm::vec3(90.0, 90.0, 90.0);
            rotation = glm::vec3(0.0, 0.0, 0.0);
        }

        void Model::setProgram(GLuint programId)
        {
            m_program = programId;
        }

        void Model::setTexture(const std::string & textureName, GLuint textureId)
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

        GLuint Model::getTextureId(const std::string& texture) const
        {
            return m_textures.at(texture);
        }

        GLuint Model::getVao() const
        {
            return m_vao;
        }

        GLuint Model::getProgram() const
        {
            return m_program;
        }

        std::vector<GLuint> Model::getVbos() const
        {
            return m_vbos;
        }

        void Model::destroy()
        {
            glDeleteVertexArrays(1, &m_vao);
            glDeleteBuffers(static_cast<GLsizei>(m_vbos.size()), &m_vbos[0]);
            m_vbos.clear();
        }

        void Model::update()
        {
            rotation = 0.01f * rotation_speed + rotation;
            rotation_sin = glm::vec3(rotation.x * PI / 180, rotation.y * PI / 180, rotation.z * PI / 180);
        }

    }

}

