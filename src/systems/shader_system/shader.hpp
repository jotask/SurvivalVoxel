#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

namespace aiko
{

    class Shader
    {
    public:
        Shader() = delete;
        Shader(const Shader&) = delete;
        Shader& operator= (const Shader&) = delete;

        Shader(const std::string name, const GLuint id, const GLuint vertexShaderId, const GLuint fragmentShaderId);
        ~Shader();

        GLuint getProgramId() const;

        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setVec2(const std::string& name, glm::vec2& value) const;
        void setVec2(const std::string& name, float x, float y) const;
        void setVec3(const std::string& name, glm::vec3& value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;
        void setVec4(const std::string& name, glm::vec4& value) const;
        void setVec4(const std::string& name, float x, float y, float z, float w) const;
        void setMat2(const std::string& name, glm::mat2& value) const;
        void setMat3(const std::string& name, glm::mat3& value) const;
        void setMat4(const std::string& name, glm::mat4& value) const;

        void use();
        void unuse();

    private:

        GLint getUniformLocation(const std::string& uniformName) const;

        const std::string m_shaderName;
        const GLuint m_programId;
        const GLuint m_vertexShaderId;
        const GLuint m_fragmentShaderId;

    };

}