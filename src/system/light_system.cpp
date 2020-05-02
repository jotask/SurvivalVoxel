#include "system/light_system.hpp"

#include "system/imgui_system.hpp"
#include "system/shader_system.hpp"

#include "imgui.h"

namespace engine
{
    LightSystem::LightSystem()
        : m_renderImgui(false)
        , m_imguiSystem(nullptr)
        , m_shaderSystem(nullptr)
    {

    }

    bool LightSystem::connect(SystemConnector & connector)
    {
        m_imguiSystem = connector.findSystem<ImguiSystem>();
        m_shaderSystem = connector.findSystem<ShaderSystem>();

        return true;
    }

    bool LightSystem::init()
    {
        m_imguiSystem->registerSystem("LightSystem", m_renderImgui);

        auto light = Light();
        light.position = { 0.f, 15.f, 0.f };
        light.color = { (1.f, 1.f, 1.f) };
        addLight(light);

        return true;
    }

    void LightSystem::preUpdate()
    {

    }

    void LightSystem::update()
    {

    }

    void LightSystem::postUpdate()
    {

    }

    void LightSystem::preRender()
    {

    }

    void LightSystem::render()
    {
        if (m_renderImgui == true)
        {
            ImGui::Begin("Light", &m_renderImgui);
            for (auto i = 0 ; i < m_lights.size() ; i++)
            {
                auto& light = m_lights[i];
                const auto lightName = "Light: " + std::to_string(i);
                ImGui::Text(lightName.c_str());
                ImGui::SliderFloat3("Position", &light.position.x, 0 , 500);
                ImGui::ColorEdit3("Color", &light.color.x);
            }
            ImGui::End();
        }

        auto shader = m_shaderSystem->getShader("chunkShader");
        for (auto & light : m_lights)
        {
            shader.setVec3("u_lightPos", light.position.x, light.position.y, light.position.z);
            shader.setVec3("u_lightCol", light.color.x, light.color.y, light.color.z);
        }
    }

    void LightSystem::postRender()
    {

    }

    void LightSystem::addLight(Light & l)
    {
        m_lights.push_back(l);
    }

}
