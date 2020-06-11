#include "texture2D.hpp"

#include <spdlog/spdlog.h>

namespace aiko
{
    Texture2D::Texture2D()
        : m_id(-1)
        , m_width(0)
        , m_height(0)
        , m_internalFormat(GL_RGB)
        , m_imageFormat(GL_RGB)
        , m_wrap_S(GL_REPEAT)
        , m_wrap_T(GL_REPEAT)
        , m_filterMin(GL_LINEAR)
        , m_filterMax(GL_LINEAR)
    {

    }

    GLuint Texture2D::getId() const
    {
        return m_id;
    }

    void Texture2D::init()
    {
        if (m_id == -1)
        {
            glGenTextures(1, &m_id);
        }
        else
        {
            spdlog::error("Attempting to generate the same texture twice. Skipping this process as texture has already been generated");
        }
    }

    void Texture2D::generate(GLuint width, GLuint height, unsigned char * data)
    {
        m_width = width;
        m_height = height;
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_imageFormat, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_S);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_T);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2D::bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

}
