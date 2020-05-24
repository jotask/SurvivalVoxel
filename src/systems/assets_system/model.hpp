#pragma once

#include "systems/shader_system/shader.hpp"
#include "systems/assets_system/texture.hpp"
#include "systems/assets_system/mesh.hpp"

#include "assimp/material.h"

#include <string>
#include <vector>

// TODO : To delete
struct aiNode;
struct aiScene;
struct aiMaterial;
struct aiMesh;

namespace aiko
{

    class Model
    {
    public:

        Model(std::string path);
        ~Model();

        void render(Shader&);

    private:

        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<aiko::Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string name);
        GLint textureFromFile(const char* path, std::string directory);

        std::vector<Mesh>   m_meshes;
        std::string         m_directory;
        std::vector<aiko::Texture> m_textures_loaded;

    };

}
