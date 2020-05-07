#include "light_system.hpp"

#include "system/imgui_system.hpp"
#include "system/entity_component_system/entity.hpp"
#include "system/shader_system/shader_system.hpp"
#include "system/entity_component_system/entity_component_system.hpp"

#include <imgui.h>

namespace engine
{
    LightSystem::LightSystem()
        : m_renderImgui(false)
        , m_imguiSystem(nullptr)
        , m_shaderSystem(nullptr)
        , m_entitySystem(nullptr)
    {

    }

    bool LightSystem::connect(SystemConnector & connector)
    {
        m_imguiSystem = connector.findSystem<ImguiSystem>();
        m_shaderSystem = connector.findSystem<ShaderSystem>();
        m_entitySystem = connector.findSystem<EntityComponentSystem>();
        return true;
    }

    bool LightSystem::init()
    {
        m_imguiSystem->registerSystem("LightSystem", m_renderImgui);

        addLight({ 0.f, 500.f, 0.f }, { 1.f, 1.f, 1.f }, { 0.5f, 0.5f, 0.5f }, { 0.f , 0.f, 0.f }, { 1.f , 1.f , 1.f });

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
                auto& light = m_entitySystem->getEntityByIdInTag(m_lights[i], entity::EntityTag::LIGHT).getComponent<Light>();
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
            for (auto& lightId : m_lights)
            {
                auto& light = m_entitySystem->getEntityByIdInTag(lightId, entity::EntityTag::LIGHT).getComponent<Light>();
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

    void LightSystem::addLight(glm::vec3 position, glm::vec3 color, glm::vec3 diffuse, glm::vec3 ambient, glm::vec3 specular)
    {
        auto& entity = m_entitySystem->addEntity(entity::EntityTag::LIGHT);
        auto& light = entity.addComponent<Light>(&entity);
        light.position = position;
        light.color = color;
        light.diffuse = diffuse;
        light.ambient = ambient;
        light.specular = specular;
        m_lights.push_back(light.getEntity()->getId());
    }

}
