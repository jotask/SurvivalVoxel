#include "shader.hpp"

namespace aiko
{

    Shader::Shader(const GLuint id)
        : m_programId(id)
    {

    }

    Shader::~Shader()
    {
        glDeleteProgram(m_programId);
    }

    void Shader::setBool(const std::string & name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_programId, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string & name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_programId, name.c_str()), value);
    }

    void Shader::setFloat(const std::string & name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
    }

    void Shader::setVec2(const std::string & name, glm::vec2 & value) const
    {
        glUniform2fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
    }

    void Shader::setVec2(const std::string & name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(m_programId, name.c_str()), x, y);
    }

    void Shader::setVec3(const std::string & name, glm::vec3 & value) const
    {
        glUniform3fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
    }

    void Shader::setVec3(const std::string & name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(m_programId, name.c_str()), x, y, z);
    }

    void Shader::setVec4(const std::string & name, glm::vec4 & value) const
    {
        glUniform4fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
    }

    void Shader::setVec4(const std::string & name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(m_programId, name.c_str()), x, y, z, w);
    }

    void Shader::setMat2(const std::string & name, glm::mat2 & value) const
    {
        glUniformMatrix2fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void Shader::setMat3(const std::string & name, glm::mat3 & value) const
    {
        glUniformMatrix3fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void Shader::setMat4(const std::string & name, glm::mat4 & value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    GLuint Shader::getProgramId() const
    {
        return m_programId;
    }

    void Shader::use()
    {
        glUseProgram(m_programId);
    }

}
