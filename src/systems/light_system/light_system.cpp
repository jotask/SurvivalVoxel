#include "light_system.hpp"

#include "systems/imgui_system.hpp"
#include "systems/entity_component_system/entity.hpp"
#include "systems/shader_system/shader_system.hpp"
#include "systems/entity_component_system/entity_component_system.hpp"
#include "systems/light_system/debug_light_renderer.hpp"

#include <imgui.h>

namespace aiko
{
    LightSystem::LightSystem()
        : m_renderImgui(false)
        , m_renderLightCubes(true)
        , m_imguiSystem(nullptr)
        , m_shaderSystem(nullptr)
        , m_entitySystem(nullptr)
        , m_lightRenderer(nullptr)
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

        addLight({ 0.f, 100, 0.f }, { 1.f, 1.f, 1.f }, { 0.5f, 0.5f, 0.5f }, { 0.f , 0.f, 0.f }, { 1.f , 1.f , 1.f });
        addLight({ 0.f, 100, 0.f }, { 0.f, 1.f, 1.f }, { 0.5f, 0.5f, 0.5f }, { 0.f , 0.f, 0.f }, { 1.f , 1.f , 1.f });
        addLight({ 0.f, 100, 0.f }, { 0.f, 1.f, 0.f }, { 0.5f, 0.5f, 0.5f }, { 0.f , 0.f, 0.f }, { 1.f , 1.f , 1.f });

        m_lightRenderer = std::make_unique<DebugLightRenderer>();
        m_lightRenderer->init();

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
            ImGui::Checkbox("Draw Debug light markers", &m_renderLightCubes);
            for (auto i = 0 ; i < m_lights.size() ; i++)
            {
                ImGui::PushID(i);
                auto& light = m_entitySystem->getEntityByIdInTag(m_lights[i], entity::EntityTag::LIGHT).getComponent<Light>();
                const auto lightName = "Light: " + std::to_string(i);
                ImGui::Text(lightName.c_str());
                ImGui::SliderFloat3("Position", &light.position.x, -50 , 50);
                ImGui::ColorEdit3("Color", &light.color.x);
                ImGui::SliderFloat3("ambient", &light.ambient.x, 0.f, 1.f);
                ImGui::SliderFloat3("diffuse", &light.diffuse.x, 0.f, 1.f);
                ImGui::SliderFloat3("specular", &light.specular.x, 0.f, 1.f);
                ImGui::PopID();
            }
            ImGui::End();
        }

        for (auto& shaderPair : m_shaderSystem->getShaders())
        {
            auto& shader = shaderPair.second;
            shader->use();
            constexpr auto MAX_LIGHT_NUMBER = 4;
            for (auto i = 0u ; i < MAX_LIGHT_NUMBER; i++)
            {
                if (i < m_lights.size())
                {
                    auto& light = m_entitySystem->getEntityByIdInTag(m_lights[i], entity::EntityTag::LIGHT).getComponent<Light>();
                    shader->setVec3("light[" + std::to_string(i) + "].position", light.position);
                    shader->setVec3("light[" + std::to_string(i) + "].color", light.color);
                }
                else
                {
                    shader->setVec3("light[" + std::to_string(i) + "].position", glm::vec3(0.f));
                    shader->setVec3("light[" + std::to_string(i) + "].color", glm::vec3(0.f));
                }
            }

            shader->unuse();
        }

        if (m_lightRenderer!= nullptr && m_renderLightCubes == true)
        {
            auto& shader = m_shaderSystem->getShader("lightShader");
            shader.use();
            auto model = glm::mat4(1.0f);
            for (const auto& l : m_lights)
            {
                auto& light = m_entitySystem->getEntityByIdInTag(l, entity::EntityTag::LIGHT).getComponent<Light>();

                model = glm::mat4(1.0f);
                model = glm::translate(model, light.position);
                model = glm::scale(model, glm::vec3(0.5f));

                shader.setMat4("model", model);
                shader.setVec3("lightColor", light.color);
                m_lightRenderer->render();
            }
            shader.unuse();
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
