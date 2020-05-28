#pragma once

#include <glm/glm.hpp>

namespace aiko
{
    struct VertexInfo
    {

    public:

        VertexInfo(const glm::vec3& vertexPosition, const glm::vec3 normal, const glm::vec4& color, const glm::vec2& vertexTexture)
            : m_position(vertexPosition)
            , m_normal(normal)
            , m_color(color)
            , m_texture(vertexTexture)
        {

        }

        VertexInfo(const glm::vec3& vertexPosition, const glm::vec4& color, const glm::vec2& vertexTexture, const glm::vec3 normal = glm::vec3(0.0f))
            : m_position(vertexPosition)
            , m_normal(normal)
            , m_color(color)
            , m_texture(vertexTexture)
        {

        }

        glm::vec3 getVertexPosition() const
        {
            return m_position;
        }

        glm::vec3 getVertexNormal() const
        {
            return m_normal;
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
        glm::vec3 m_normal;
        glm::vec4 m_color;
        glm::vec2 m_texture;

    };
}

