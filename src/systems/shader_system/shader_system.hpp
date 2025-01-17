#pragma once

#include "systems/system_interface.hpp"
#include "systems/shader_system/shader.hpp"

#include <glad/glad.h>

#include <string>
#include <map>

namespace aiko
{

    class ShaderSystem : public System
    {
    public:

        ShaderSystem();
        virtual ~ShaderSystem() override;

        virtual bool init() override;

        Shader& getShader(const std::string shader = "staticShader");

        std::map<const std::string, AikoUPtr<Shader>>& getShaders();

    private:

        void createProgram(const std::string& shaderName, const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);

        GLuint createShader(GLenum shader_type, const std::string& file, const std::string& source, const std::string& shaderName);

        std::map<const std::string, AikoUPtr<Shader>> m_programs;

    };

}
