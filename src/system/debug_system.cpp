#include "system/debug_system.hpp"

#include "system/imgui_system.hpp"
#include "system/shader_system.hpp"

#include "imgui.h"

namespace engine
{
    DebugSystem::DebugSystem()
        : m_renderImgui(false)
        , m_imguiSystem(nullptr)
        , m_shaderSystem(nullptr)
    {

    }

    bool DebugSystem::connect(SystemConnector & connector)
    {
        m_imguiSystem = connector.findSystem<ImguiSystem>();
        m_shaderSystem = connector.findSystem<ShaderSystem>();

        return true;
    }

    bool DebugSystem::init()
    {
        m_imguiSystem->registerSystem("DebugSystem", m_renderImgui);
        return true;
    }

    void DebugSystem::preUpdate()
    {

    }

    void DebugSystem::update()
    {

    }

    void DebugSystem::postUpdate()
    {

    }

    void DebugSystem::preRender()
    {

    }

    void DebugSystem::render()
    {

    }

    void DebugSystem::postRender()
    {

    }

}
