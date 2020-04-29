#include "system/render_system.hpp"

#include "system/display_system.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine
{
    RenderSystem::RenderSystem()
        : m_displaySystem(nullptr)
    {

    }

    bool RenderSystem::init()
    {
        glEnable(GL_DEPTH_TEST);
        return true;
    }

    bool RenderSystem::connect(SystemConnector & connector)
    {
        m_displaySystem = connector.findSystem<DisplaySystem>();
        return true;
    }

    void RenderSystem::preUpdate()
    {

    }

    void RenderSystem::update()
    {

    }

    void RenderSystem::postUpdate()
    {

    }

    void RenderSystem::preRender()
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    void RenderSystem::render()
    {

    }

    void RenderSystem::postRender()
    {

    }

    void RenderSystem::swapBuffers() const
    {
        glfwSwapBuffers(m_displaySystem->getWindow());
    }

}
