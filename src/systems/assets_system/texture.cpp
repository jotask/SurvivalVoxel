#include "texture.hpp"

namespace aiko
{

    Texture::Texture(const GLuint id, std::string type, std::string path)
        : Asset(AssetType::Texture)
        , m_id(id)
        , m_type(type)
        , m_path(path)
    {

    }

    bool Texture::load()
    {
        return false;
    }

    GLuint Texture::getId() const
    {
        return m_id;
    }

    std::string Texture::getType() const
    {
        return m_type;
    }

    std::string Texture::getPath() const
    {
        return m_path;
    }

}
