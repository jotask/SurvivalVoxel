#include "model.hpp"

#include "systems/render_system/vertex_info.hpp"
#include "systems/entity_component_system/entity.hpp"

#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SOIL2.h>

#include <iostream>

namespace aiko
{

    Model::Model(Entity* entity, Shader& shader, std::string path)
        : Component(entity)
        , m_shader(shader)
        , m_path(path)
    {

    }

    void Model::load()
    {
        loadModel(m_path);
    }

    void Model::render()
    {
        m_shader.setMat4("model", getEntity()->getTransform().getModelMatrix());
        for (GLuint i = 0; i < m_meshes.size(); i++)
        {
            m_meshes[i].render(m_shader);
        }
    }

    void Model::loadModel(std::string path)
    {
        Assimp::Importer importer;
        const auto* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (scene == nullptr || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
        {
            std::cout << "Error::Assimp:: " << importer.GetErrorString() << std::endl;
            return;
        }

        m_directory = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene);

    }

    void Model::processNode(aiNode* node, const aiScene* scene)
    {
        for (GLuint i = 0 ; i < node->mNumMeshes; i++)
        {
            auto* mesh = scene->mMeshes[node->mMeshes[i]];
            m_meshes.push_back(processMesh(mesh, scene));
        }
        for (GLuint i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<VertexInfo> vertices;
        std::vector<GLuint> indices;
        std::vector<aiko::Texture> textures;

        for (GLuint i = 0; i < mesh->mNumVertices; i++)
        {

            
            glm::vec3 position;
            position.x = mesh->mVertices[i].x;
            position.y = mesh->mVertices[i].y;
            position.z = mesh->mVertices[i].z;

            glm::vec3 normal;
            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;

            const auto color = glm::vec4( 1.0f , 1.0f , 1.0f , 1.0f );

            glm::vec2 uv;
            if (mesh->mTextureCoords[0] != nullptr)
            {
                uv.x = mesh->mTextureCoords[0][i].x;
                uv.y = mesh->mTextureCoords[0][i].y;
            }

            vertices.push_back({ position, normal, color, uv });

        }

        for (GLuint i = 0 ; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (GLuint j = 0 ; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            {
                // loadMaterialTextures(material, aiTextureType_NONE, "texture_none");
                // loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_none");
                // loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_none");
                // loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_none");
                // loadMaterialTextures(material, aiTextureType_EMISSIVE, "texture_none");
                // loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_none");
                // loadMaterialTextures(material, aiTextureType_NORMALS, "texture_none");
                // loadMaterialTextures(material, aiTextureType_SHININESS, "texture_none");
                // loadMaterialTextures(material, aiTextureType_OPACITY, "texture_none");
                // loadMaterialTextures(material, aiTextureType_DISPLACEMENT, "texture_none");
                // loadMaterialTextures(material, aiTextureType_LIGHTMAP, "texture_none");
                // loadMaterialTextures(material, aiTextureType_REFLECTION, "texture_none");
                // loadMaterialTextures(material, aiTextureType_UNKNOWN, "texture_none");
                // textures.insert(textures.end(), texts.begin(), texts.end());
            }

            {
                std::vector<aiko::Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
                textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            }

            {
                std::vector<aiko::Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
                textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
            }

            {
                std::vector<aiko::Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
                textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
            }

            {
                std::vector<aiko::Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
                textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
            }

        }

        return Mesh(vertices, indices, textures);

    }

    std::vector<aiko::Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName)
    {
        std::vector<aiko::Texture> textures;
        const auto tmp = material->GetTextureCount(type);
        for (GLuint i = 0 ; i < tmp ; i ++)
        {
            aiString str;
            material->GetTexture(type, i, &str);

            GLboolean skip = false;

            for (GLuint j = 0 ; j < m_textures_loaded.size(); j++)
            {
                aiString path = aiString(m_textures_loaded[j].getPath());
                if (path == str)
                {
                    textures.push_back(m_textures_loaded[j]);
                    skip = true;
                    break;
                }
            }

            if (skip == false)
            {

                const auto id = textureFromFile(str.C_Str(), m_directory);
                auto texture = aiko::Texture(id, typeName, str.C_Str());
                textures.push_back(texture);
                m_textures_loaded.push_back(texture);

            }

        }
        return textures;
    }

    GLint Model::textureFromFile(const char* path, std::string directory)
    {
        std::string fileName = std::string(path);
        fileName = directory + '/' + fileName;

        GLuint textureId;

        glGenTextures(1, &textureId);
        int width;
        int height;
        unsigned char* image = SOIL_load_image(fileName.c_str(), &width, &height, 0 , SOIL_LOAD_RGB);

        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexImage2D(GL_TEXTURE, 0, GL_RGB, width, height, 0 , GL_RGB, GL_UNSIGNED_BYTE, image);

        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        SOIL_free_image_data(image);

        return textureId;

    }

}
