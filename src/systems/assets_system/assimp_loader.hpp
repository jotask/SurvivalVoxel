#pragma once

#include "systems/assets_system/model.hpp"
#include "systems/shader_system/shader_system.hpp"
#include "systems/assets_system/texture_loader.hpp"
#include "systems/assets_system/assets_system.hpp"
#include "engine.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glad/glad.h>


#include <optional>
#include <string>
#include <iostream>
#include <filesystem>

namespace aiko
{
    namespace loader
    {
        namespace assimp
        {

            static std::vector<Texture*> processMaterial(AssetsSystem* sys, aiMaterial* material, std::string directory)
            {
                auto textures = std::vector<Texture*>();
                {
                    auto diffuseMaps = texture::loadMaterialTextures(sys, material, aiTextureType_DIFFUSE, "texture_diffuse", directory);
                    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
                }

                {
                    auto specularMaps = texture::loadMaterialTextures(sys, material, aiTextureType_SPECULAR, "texture_specular", directory);
                    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
                }

                {
                    auto normalMaps = texture::loadMaterialTextures(sys, material, aiTextureType_HEIGHT, "texture_normal", directory);
                    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
                }

                {
                    auto heightMaps = texture::loadMaterialTextures(sys, material, aiTextureType_AMBIENT, "texture_height", directory);
                    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
                }
                return textures;
            }

            static Mesh* processMesh(AssetsSystem* sys, aiMesh* mesh, const aiScene* scene, std::string directory)
            {

                std::vector<VertexInfo> vertices;
                std::vector<GLuint> indices;
                std::vector<aiko::Texture*> textures;

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


                    const aiMaterial *mtl = scene->mMaterials[mesh->mMaterialIndex];

                    auto color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                    aiColor4D diffuse;
                    if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
                    {
                        color = { diffuse.r, diffuse.g, diffuse.b, diffuse.a };
                    }

                    glm::vec2 uv;
                    if (mesh->mTextureCoords[0] != nullptr)
                    {
                        uv.x = mesh->mTextureCoords[0][i].x;
                        uv.y = mesh->mTextureCoords[0][i].y;
                    }

                    vertices.push_back({ position, normal, color, uv });

                }

                for (GLuint i = 0; i < mesh->mNumFaces; i++)
                {
                    aiFace face = mesh->mFaces[i];
                    for (GLuint j = 0; j < face.mNumIndices; j++)
                    {
                        indices.push_back(face.mIndices[j]);
                    }
                }

                if (mesh->mMaterialIndex >= 0)
                {
                    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
                    auto texts = processMaterial(sys, material, directory);
                    for (auto t : texts)
                    {
                        textures.push_back(t);
                    }
                }

                auto& meshes = sys->getAssets(AssetType::Mesh);

                meshes.emplace_back(std::make_unique<Mesh>(MeshData(vertices, indices)));

                return static_cast<Mesh*>(meshes[meshes.size() - 1].get());

            }

            static void processNode(AssetsSystem* sys, Model& model, aiNode* node, const aiScene* scene, std::string directory)
            {
                for (GLuint i = 0; i < node->mNumMeshes; i++)
                {
                    auto* aiMesh = scene->mMeshes[node->mMeshes[i]];
                    auto* mesh = processMesh(sys, aiMesh, scene, directory);
                    mesh->load();
                    model.addMesh(mesh);
                }
                for (GLuint i = 0; i < node->mNumChildren; i++)
                {
                    processNode(sys, model, node->mChildren[i], scene, directory);
                }
            }

            static std::optional<Model> loadModel(AssetsSystem* sys, const std::string name, const std::string file, const std::string shaderName)
            {

                Assimp::Importer importer;

                const auto path = (std::filesystem::current_path() / "../assets/" / file).u8string();

                const auto* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

                if (scene == nullptr || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
                {
                    std::cout << "Error::Assimp:: " << importer.GetErrorString() << std::endl;
                    return std::nullopt;
                }

                auto directory = path.substr(0, path.find_last_of('/'));

                auto* shaderSystem = Engine::getInstance().getSystem<ShaderSystem>();
                auto& shader = shaderSystem->getShader(shaderName);

                auto model = Model(shader);

                processNode(sys, model, scene->mRootNode, scene, directory);

                return std::move(model);
            }

        }
    }
}

