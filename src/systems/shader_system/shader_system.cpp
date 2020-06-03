#include "shader_system.hpp"

#include "utils/utilities.hpp"
#include "utils/json_loader.hpp"

#include <Shadinclude.hpp>

#include <algorithm>

namespace aiko
{
    ShaderSystem::ShaderSystem()
    {

    }

    ShaderSystem::~ShaderSystem()
    {
        m_programs.clear();
    }

    bool ShaderSystem::init()
    {

        auto shadersJson = jsonLoader::loadJson("../assets/shaders.json");

        const auto folderForShaders = shadersJson["folder"].asString() + "/";

        const auto shadersList = shadersJson["shaders"];
        for (auto i = 0u; i < shadersList.size(); i++)
        {
            const auto name = shadersList[i]["name"].asString();
            const auto vertex = shadersList[i]["vertex"].asString();
            const auto fragment = shadersList[i]["fragment"].asString();
            createProgram(name, folderForShaders + vertex, folderForShaders + fragment);
        }

        return true;
    }

    bool ShaderSystem::connect(SystemConnector & connector)
    {
        return true;
    }

    void ShaderSystem::preUpdate()
    {

    }

    void ShaderSystem::update()
    {

    }

    void ShaderSystem::postUpdate()
    {

    }

    void ShaderSystem::preRender()
    {

    }

    void ShaderSystem::render()
    {

    }

    void ShaderSystem::postRender()
    {

    }

    Shader& ShaderSystem::getShader(const std::string shader)
    {
        if (m_programs.find(shader) != m_programs.end())
        {
            return *m_programs.at(shader).get();
        }
        printf("Shader with name %s does not exist.\n", shader.c_str());
        std::terminate();
    }

    std::map<const std::string, AikoUPtr<Shader>>& ShaderSystem::getShaders()
    {
        return m_programs;
    }

    void ShaderSystem::createProgram(const std::string & shaderName, const std::string & vertexShaderFilename, const std::string & fragmentShaderFilename)
    {

        const auto vertexShaderCode = Shadinclude::load((std::filesystem::current_path() / ("../assets/" + vertexShaderFilename)).u8string());
        const auto fragmentShaderCode = Shadinclude::load((std::filesystem::current_path() / ("../assets/" + fragmentShaderFilename)).u8string());

        const auto vertexShaderId = createShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
        const auto fragmentShaderId = createShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");

        auto linkResult = GL_FALSE;

        auto program = glCreateProgram();
        glAttachShader(program, vertexShaderId);
        glAttachShader(program, fragmentShaderId);

        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

        if (linkResult == GL_FALSE) {
            int infoLogLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
            std::vector<char> program_log(infoLogLength);
            glGetProgramInfoLog(program, infoLogLength, NULL, &program_log[0]);
            printf("Shader loader LINK ERROR");
            printf("%s", &program_log[0]);
            std::terminate();
        }

        m_programs.emplace(shaderName, std::make_unique<Shader>(shaderName, program, vertexShaderId, fragmentShaderId));

    }

    GLuint ShaderSystem::createShader(GLenum shader_type, const std::string & source, const std::string & shaderName)
    {
        auto compileResult = GL_FALSE;

        const auto shader = glCreateShader(shader_type);
        const auto* shaderCodePtr = source.c_str();
        const auto shaderCodeSize = static_cast<int>(source.size());

        glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);

        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

        if (compileResult == GL_FALSE)
        {
            int infoLogLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
            std::vector<char> shader_log(infoLogLength);
            glGetShaderInfoLog(shader, infoLogLength, NULL, &shader_log[0]);
            printf("Error compiling shader %s\n", shaderName.c_str());
            printf("%s", &shader_log[0]);
            std::terminate();
        }
        return shader;
    }

}
