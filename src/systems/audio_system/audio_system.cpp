#include "systems/audio_system/audio_system.hpp"

#include "systems/imgui_system.hpp"

#include <imgui.h>

namespace aiko
{

    AudioSystem::AudioSystem()
        : m_imguiSystem(nullptr)
        , m_renderImgui(false)
    {

    }

    bool AudioSystem::connect(SystemConnector & connector)
    {
        return true;
    }

    bool AudioSystem::init()
    {

        m_imguiSystem->registerSystem("CameraSystem", m_renderImgui);

        return true;
    }

    void AudioSystem::preUpdate()
    {

    }

    void AudioSystem::update()
    {

    }

    void AudioSystem::postUpdate()
    {

    }

    void AudioSystem::preRender()
    {

    }

    void AudioSystem::render()
    {
        if (m_renderImgui == true)
        {
            ImGui::Begin("Audio settings", &m_renderImgui);
            ImGui::End();
        }
    }

    void AudioSystem::postRender()
    {

    }

}
