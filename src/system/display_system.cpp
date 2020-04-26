#include "system/display_system.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine
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

        printf("GLFW version: %s\n", glfwGetVersionString());

        m_window = glfwCreateWindow(800, 600, "Survival Voxel", nullptr, nullptr);

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

}
