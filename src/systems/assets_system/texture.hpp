#pragma once

#include <glad/glad.h>

#include <string>

namespace aiko
{

    class Texture
    {
    public:

        Texture(const GLuint id, std::string type, std::string path);
        ~Texture() = default;

        GLuint getId() const;
        std::string getType() const;
        std::string getPath() const;

    private:
        GLuint m_id;
        std::string m_type;
        std::string m_path;

    };

}
