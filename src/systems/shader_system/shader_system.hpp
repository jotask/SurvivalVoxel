#pragma once

#include "systems/system_interface.hpp"
#include "systems/shader_system/shader.hpp"

#include <glad/glad.h>

#include <string>
#include <map>

namespace engine
{

    class ShaderSystem : public System
    {
    public:

        ShaderSystem();
        virtual ~ShaderSystem() override;

        virtual bool init() override;
        virtual bool connect(SystemConnector&) override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

        Shader& getShader(const std::string&);

        std::map<const std::string, AikoUPtr<Shader>>& getShaders();

    private:

        void createProgram(const std::string& shaderName, const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);

        GLuint createShader(GLenum shader_type, const std::string& source, const std::string& shaderName);

        std::map<const std::string, AikoUPtr<Shader>> m_programs;

    };

}
