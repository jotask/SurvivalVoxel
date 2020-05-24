#pragma once

#include <glm/glm.hpp>

namespace aiko
{
    struct VertexInfo
    {

    public:
        VertexInfo(const glm::vec3& vertexPosition, const glm::vec4& vertexColor, const glm::vec3 normal = glm::vec3(0.f))
            : m_position(vertexPosition)
            , m_color(vertexColor)
            , m_normal(normal)
            , m_texture(0)
        {

        }

        VertexInfo(const glm::vec3& vertexPosition, const glm::vec2& vertexTexture, const glm::vec3 normal = glm::vec3(0.f))
            : m_position(vertexPosition)
            , m_color(0)
            , m_texture(vertexTexture)
        {

        }

        VertexInfo(const glm::vec3& vertexPosition, const glm::vec2& vertexTexture, const glm::vec3 normal, const glm::vec3 color)
            : m_position(vertexPosition)
            , m_color({color, 1.0})
            , m_texture(vertexTexture)
            , m_normal(normal)
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

