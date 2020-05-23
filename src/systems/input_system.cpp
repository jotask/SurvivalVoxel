#include "systems/input_system.hpp"

#include "systems/display_system.hpp"

#include <GLFW/glfw3.h>

namespace engine
{
    InputSystem::InputSystem()
        : m_displaySystem(nullptr)
    {

    }

    bool InputSystem::init()
    {
        return true;
    }

    bool InputSystem::connect(SystemConnector & connector)
    {
        m_displaySystem = connector.findSystem<DisplaySystem>();
        return true;
    }

    void InputSystem::preUpdate()
    {
        glfwPollEvents();
    }

    void InputSystem::update()
    {

    }

    void InputSystem::postUpdate()
    {

    }

    void InputSystem::preRender()
    {

    }

    void InputSystem::render()
    {

    }

    void InputSystem::postRender()
    {

    }

}
