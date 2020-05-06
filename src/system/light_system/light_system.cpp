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
        light.position = { 0.f, 500.f, 0.f };
        light.color = { (1.f, 1.f, 1.f) };
        light.diffuse = glm::vec3(0.5f);
        light.ambient = glm::vec3(0.f);
        light.specular = glm::vec3(1.f, 1.f, 1.f);
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
                ImGui::SliderFloat3("ambient", &light.ambient.x, 0.f, 1.f);
                ImGui::SliderFloat3("diffuse", &light.diffuse.x, 0.f, 1.f);
                ImGui::SliderFloat3("specular", &light.specular.x, 0.f, 1.f);
            }
            ImGui::End();
        }

        for (auto& shaderPair : m_shaderSystem->getShaders())
        {
            auto& shader = shaderPair.second;
            shader.use();
            for (auto & light : m_lights)
            {
                shader.setVec3("light.position", light.position);
                shader.setVec3("light.color", light.color);
                shader.setVec3("light.ambient", light.ambient);
                shader.setVec3("light.diffuse", light.diffuse);
                shader.setVec3("light.specular", light.specular);
            }
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
