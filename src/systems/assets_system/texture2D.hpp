#pragma once

#include "systems/assets_system/asset.hpp"

#include <glad/glad.h>

namespace aiko
{

    class Texture2D
    {
    public:

        Texture2D();
        ~Texture2D() = default;

        GLuint getId() const;

        void generate(GLuint width, GLuint height, unsigned char* data);

        void bind();

    private:
        GLuint m_id;
        GLuint m_width;
        GLuint m_height;
        GLuint m_internalFormat;
        GLuint m_imageFormat;
        GLuint m_wrap_S;
        GLuint m_wrap_T;
        GLuint m_filterMin;
        GLuint m_filterMax;

    };

}
