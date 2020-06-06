#pragma once

#include "systems/assets_system/asset.hpp"

#include <glad/glad.h>

#include <string>

namespace aiko
{

    class Texture : public Asset
    {
    public:

        Texture(const GLuint id, std::string type, std::string path);
        virtual ~Texture() = default;

        virtual bool load() override;

        GLuint getId() const;
        std::string getType() const;
        std::string getPath() const;

    private:
        GLuint m_id;
        std::string m_type;
        std::string m_path;

    };

}
