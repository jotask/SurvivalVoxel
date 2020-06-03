#include "shader_system.hpp"

#include "utils/utilities.hpp"

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
        createProgram("staticShader", "shaders/static_vertex_shader.glsl", "shaders/static_fragment_shader.glsl");
        createProgram("staticColorShader", "shaders/static_color_vertex_shader.glsl", "shaders/static_fragment_shader.glsl");
        createProgram("staticTextureShader", "shaders/static_texture_vertex_shader.glsl", "shaders/static_fragment_shader.glsl");
        createProgram("colorShader", "shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
        createProgram("cubeShader", "shaders/cube_vertex_shader.glsl", "shaders/cube_fragment_shader.glsl");
        createProgram("chunkShader", "shaders/chunk_vertex_shader.glsl", "shaders/chunk_fragment_shader.glsl");
        createProgram("bullet3Shader", "shaders/bullet3_vertex_shader.glsl", "shaders/bullet3_fragment_shader.glsl");
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
