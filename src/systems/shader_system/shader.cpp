#include "shader.hpp"

namespace aiko
{

    Shader::Shader(const std::string name, const GLuint id, const GLuint vertexShaderId, const GLuint fragmentShaderId)
        : m_shaderName(name)
        , m_programId(id)
        , m_vertexShaderId(vertexShaderId)
        , m_fragmentShaderId(fragmentShaderId)
    {

    }

    Shader::~Shader()
    {
        glDetachShader(m_programId, m_vertexShaderId);
        glDetachShader(m_programId, m_fragmentShaderId);
        glDeleteShader(m_vertexShaderId);
        glDeleteShader(m_fragmentShaderId);
        glDeleteProgram(m_programId);
    }

    void Shader::setBool(const std::string & name, bool value) const
    {
        glUniform1i(getUniformLocation(name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string & name, int value) const
    {
        glUniform1i(getUniformLocation(name.c_str()), value);
    }

    void Shader::setFloat(const std::string & name, float value) const
    {
        glUniform1f(getUniformLocation(name.c_str()), value);
    }

    void Shader::setVec2(const std::string & name, glm::vec2 & value) const
    {
        glUniform2fv(getUniformLocation(name.c_str()), 1, &value[0]);
    }

    void Shader::setVec2(const std::string & name, float x, float y) const
    {
        glUniform2f(getUniformLocation(name.c_str()), x, y);
    }

    void Shader::setVec3(const std::string & name, glm::vec3 & value) const
    {
        glUniform3fv(getUniformLocation(name.c_str()), 1, &value[0]);
    }

    void Shader::setVec3(const std::string & name, float x, float y, float z) const
    {
        glUniform3f(getUniformLocation(name.c_str()), x, y, z);
    }

    void Shader::setVec4(const std::string & name, glm::vec4 & value) const
    {
        glUniform4fv(getUniformLocation(name.c_str()), 1, &value[0]);
    }

    void Shader::setVec4(const std::string & name, float x, float y, float z, float w) const
    {
        glUniform4f(getUniformLocation(name.c_str()), x, y, z, w);
    }

    void Shader::setMat2(const std::string & name, glm::mat2 & value) const
    {
        glUniformMatrix2fv(getUniformLocation(name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void Shader::setMat3(const std::string & name, glm::mat3 & value) const
    {
        glUniformMatrix3fv(getUniformLocation(name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void Shader::setMat4(const std::string & name, glm::mat4 & value) const
    {
        glUniformMatrix4fv(getUniformLocation(name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    GLuint Shader::getProgramId() const
    {
        return m_programId;
    }

    void Shader::use()
    {
        glUseProgram(m_programId);
    }

    void Shader::unuse()
    {
        glUseProgram(0);
    }

    GLint Shader::getUniformLocation(const std::string & uniformName) const
    {
        return glGetUniformLocation(m_programId, uniformName.c_str());
    }

}
