#include "systems/display_system.hpp"

#include "systems/event_system/event_system.hpp"
#include "systems/event_system/engine_events.hpp"
#include "utils/json_loader.hpp"

#include "json/json.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace aiko
{
    DisplaySystem::DisplaySystem()
        : m_window(nullptr)
    {

    }

    DisplaySystem::~DisplaySystem()
    {
        glfwTerminate();
    }

    bool DisplaySystem::init()
    {
        if (glfwInit() == false)
        {
            fprintf(stderr, "Failed to init GLFW\n");
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        printf("GLFW version: %s\n", glfwGetVersionString());

        const auto json = jsonLoader::loadJson("../config/window.json");

        const auto width = json["window"]["size"]["width"].asInt();
        const auto height = json["window"]["size"]["height"].asInt();
        const auto tittle = json["window"]["tittle"].asString();

        m_window = glfwCreateWindow(width, height, tittle.c_str(), nullptr, nullptr);

        if (m_window == nullptr)
        {
            fprintf(stderr, "Failed to create GLFW window");
            return false;
        }

        glfwMakeContextCurrent(m_window);

        if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false)
        {
            fprintf(stderr, "Failed to init GLAD\n");
            return false;
        }

        printf("OpenGL version: %s\n", glGetString(GL_VERSION));

        glfwSwapInterval(1);

        glfwSetWindowSizeCallback(m_window,  [](GLFWwindow* window, int width, int height) { EventSystem::it().sendEvent(WindowResizeEvent(width, height)); });
        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) { EventSystem::it().sendEvent(WindowCloseEvent()); });

        int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {

            auto glDebugOutput = [](GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam)
            {
                // ignore non-significant error/warning codes
                if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

                std::cout << "---------------" << std::endl;
                std::cout << "Debug message (" << id << "): " << message << std::endl;

                switch (source)
                {
                case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
                case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
                case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
                case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
                case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
                } std::cout << std::endl;

                switch (type)
                {
                case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
                case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
                case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
                case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
                case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
                case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
                case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
                } std::cout << std::endl;

                switch (severity)
                {
                case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
                case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
                case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
                case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
                } std::cout << std::endl;
                std::cout << std::endl;
            };

            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(glDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

        }

        return true;

    }

    bool DisplaySystem::connect(SystemConnector &)
    {
        return true;
    }

    void DisplaySystem::preUpdate()
    {

    }

    void DisplaySystem::update()
    {

    }

    void DisplaySystem::postUpdate()
    {

    }

    void DisplaySystem::preRender()
    {

    }

    void DisplaySystem::render()
    {

    }

    void DisplaySystem::postRender()
    {

    }

    GLFWwindow * DisplaySystem::getWindow() const
    {
        return m_window;
    }

    glm::vec2 DisplaySystem::getWindowSize() const
    {
        int width = 0;
        int height = 0;
        glfwGetWindowSize(m_window, &width, &height);
        return glm::vec2(width, height);
    }

    bool DisplaySystem::shouldWindowClose() const
    {
        return glfwWindowShouldClose(m_window);
    }

}
