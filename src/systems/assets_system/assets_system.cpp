#include "systems/assets_system/assets_system.hpp"

#include "systems/imgui_system.hpp"
#include "systems/entity_component_system/entity_component_system.hpp"
#include "systems/entity_component_system/entity.hpp"
#include "systems/shader_system/shader_system.hpp"

#include <imgui.h>

#include <filesystem>

namespace aiko
{
    AssetsSystem::AssetsSystem()
        : m_imguiSystem(nullptr)
        , m_entityComponentSystem(nullptr)
        , m_shaderSystem(nullptr)
        , m_renderImgui(false)
    {

    }

    bool AssetsSystem::connect(SystemConnector & connector)
    {
        m_imguiSystem = connector.findSystem<ImguiSystem>();
        m_entityComponentSystem = connector.findSystem<EntityComponentSystem>();
        m_shaderSystem = connector.findSystem<ShaderSystem>();
        return true;
    }

    bool AssetsSystem::init()
    {
        m_imguiSystem->registerSystem("AssetsSystem", m_renderImgui);

        auto fullPathToFile = std::filesystem::current_path() / ("../assets/dragon.obj");

        loadModel(fullPathToFile.u8string());

        return true;
    }

    void AssetsSystem::render()
    {
        if (m_renderImgui == true)
        {
            ImGui::Begin("AssetsSystem", &m_renderImgui);
            ImGui::Text("Assets Loaded: " + m_models.size());
            ImGui::End();
        }
    }

    void AssetsSystem::loadModel(const std::string path)
    {
        auto& shader = m_shaderSystem->getShader("chunkShader");

        auto& entity = m_entityComponentSystem->addEntity();
        auto& model = entity.addComponent<Model>(&entity, shader, path);
        model.load();
        m_models.push_back(std::move(model));
    }

}
