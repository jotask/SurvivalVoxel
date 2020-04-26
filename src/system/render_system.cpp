#include "system/render_system.hpp"

namespace engine
{
    RenderSystem::RenderSystem()
        : m_displaySystem(nullptr)
    {

    }

    bool RenderSystem::init()
    {
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
