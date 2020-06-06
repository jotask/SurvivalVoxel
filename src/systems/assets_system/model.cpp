#include "model.hpp"

#include "systems/render_system/vertex_info.hpp"
#include "systems/entity_component_system/entity.hpp"

#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SOIL2.h>

#include <imgui.h>

#include <iostream>

namespace aiko
{

    Model::Model(Shader& shader)
        : Asset(AssetType::Model)
        , m_shader(shader)
    {

    }

    bool Model::load()
    {
        return false;
    }

    void Model::addMesh(Mesh* mesh)
    {
        m_meshes.push_back(mesh);
    }

    void Model::addTexture(Texture* texture)
    {
        m_textures.push_back(texture);
    }

    void Model::render(glm::mat4 modelMatrix)
    {

        static auto shineDamper = 1.0f;
        static auto reflectivity = 0.0f;

        {
            if (ImGui::Begin("test") == true)
            {
                ImGui::SliderFloat("shineDamper", &shineDamper, 0.0f, 1.0f);
                ImGui::SliderFloat("reflectivity", &reflectivity, 0.0f, 1.0f);
            }
            ImGui::End();
        }

        m_shader.use();
        m_shader.setMat4("model", modelMatrix);
        m_shader.setFloat("shineDamper", shineDamper);
        m_shader.setFloat("reflectivity", reflectivity);
        m_shader.unuse();
        for (GLuint i = 0; i < m_meshes.size(); i++)
        {
            m_meshes[i]->render(m_shader);
        }
    }

}
