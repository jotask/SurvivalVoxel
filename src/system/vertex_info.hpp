#pragma once

#include <glm/glm.hpp>

namespace engine
{
    struct VertexInfo
    {

    public:
        VertexInfo(const glm::vec3& vertexPosition, const glm::vec4& vertexColor)
            : m_position(vertexPosition)
            , m_color(vertexColor)
            , m_texture(0)
        {

        }
        
        VertexInfo(const glm::vec3& vertexPosition, const glm::vec2& vertexTexture)
            : m_position(vertexPosition)
            , m_color(0)
            , m_texture(vertexTexture)
        {

        }

        glm::vec3 getVertexPosition() const
        {
            return m_position;
        }

        glm::vec4 getVertexColor() const
        {
            return m_color;
        }

        glm::vec2 getVertexTexture() const
        {
            return m_texture;
        }

    // private:
        glm::vec3 m_position;
        glm::vec4 m_color;
        glm::vec2 m_texture;

    };
}

