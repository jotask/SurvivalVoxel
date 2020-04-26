#include "system/shader_system.hpp"

#include <algorithm>
#include <fstream>
#include <filesystem>

namespace engine
{
    ShaderSystem::ShaderSystem()
    {

    }

    ShaderSystem::~ShaderSystem()
    {
        auto deleteShader = [](auto& entry) {
            auto shaderId = entry.second;
            glDeleteProgram(shaderId);
        };
        std::for_each(m_programs.begin(), m_programs.end(), deleteShader);
        m_programs.clear();
    }

    bool ShaderSystem::init()
    {
        createProgram("colorShader", "vertex_shader.glsl", "fragment_shader.glsl");
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

    GLuint ShaderSystem::getShader(const std::string & shader) const
    {
        if (m_programs.find(shader) != m_programs.end())
        {
            return m_programs.at(shader);
        }
        printf("Shader with name %s does not exist.\n", shader.c_str());
        std::terminate();
        return 0;
    }

    void ShaderSystem::createProgram(const std::string & shaderName, const std::string & vertexShaderFilename, const std::string & fragmentShaderFilename)
    {
        const auto vertexShaderCode = readShader(vertexShaderFilename);
        const auto fragmentShaderCode = readShader(fragmentShaderFilename);

        const auto vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
        const auto fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");

        auto linkResult = GL_FALSE;

        auto program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

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

        m_programs[shaderName] = program;
    }

    std::string ShaderSystem::readShader(const std::string& fileName)
    {

        // TODO : Not happy with this, find other solution
        auto fullPathToFile = std::filesystem::current_path() / ("../assets/" + fileName);

        std::string shaderCode;
        std::ifstream file(fullPathToFile, std::ios::in);

        if (file.good() == false)
        {
            printf("Cannot read shader file %s\n", fileName.c_str());
            std::terminate();
        }

        file.seekg(0, std::ios::end);
        shaderCode.resize(static_cast<unsigned int>(file.tellg()));
        file.seekg(0, std::ios::beg);
        file.read(&shaderCode[0], shaderCode.size());
        file.close();
        return shaderCode;
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
