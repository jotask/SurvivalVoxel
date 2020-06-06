#pragma once

#include "systems/shader_system/shader.hpp"
#include "systems/assets_system/texture.hpp"
#include "systems/assets_system/mesh.hpp"
#include "systems/assets_system/asset.hpp"

#include "assimp/material.h"

#include <string>
#include <vector>

namespace aiko
{

    class Entity;

    class Model : public Asset
    {
    public:

        Model(Shader& shader);
        ~Model() = default;

        virtual bool load() override;

        void addMesh(Mesh* mesh);
        void addTexture(Texture* texture);

        void render();

    private:

        Shader&             m_shader;
        std::vector<Mesh*>   m_meshes;
        std::vector<aiko::Texture*> m_textures;

    };

}
