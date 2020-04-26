#pragma once

#include "system/system_interface.hpp"

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

        GLuint getShader(const std::string&) const;

    private:

        void createProgram(const std::string& shaderName, const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);

        std::string readShader(const std::string& fileName);

        GLuint createShader(GLenum shader_type, const std::string& source, const std::string& shaderName);

        std::map<std::string, GLuint> m_programs;

    };

}
