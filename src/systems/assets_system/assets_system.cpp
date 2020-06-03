#include "systems/assets_system/assets_system.hpp"

#include "systems/imgui_system.hpp"
#include "systems/entity_component_system/entity_component_system.hpp"
#include "systems/entity_component_system/entity.hpp"
#include "systems/shader_system/shader_system.hpp"
#include "utils/json_loader.hpp"

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

        auto assetsJson = jsonLoader::loadJson("../assets/assets.json");

        const auto modelFolder = assetsJson["folder"].asString() + "/";

        const auto assetsList = assetsJson["assets"];
        for (auto i = 0u ; i < assetsList.size(); i++)
        {
            const auto load = assetsList[i]["load"].asBool();
            if(load == true)
            {
                const auto name = assetsList[i]["name"].asString();
                const auto file = assetsList[i]["file"].asString();
                const auto shader = assetsList[i]["shader"].asString();

                loadModel(name, modelFolder + file, shader);

            }

        }
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

    void AssetsSystem::loadModel(const std::string name, const std::string file, const std::string shaderName)
    {
        auto& shader = m_shaderSystem->getShader(shaderName);

        auto& entity = m_entityComponentSystem->addEntity();

        auto fullPathToFile = std::filesystem::current_path() / ("../assets/models/box.obj");

        auto tmp = (std::filesystem::current_path() / "../assets/" /file).u8string();

        auto& model = entity.addComponent<Model>(&entity, shader, tmp);
        model.load();
        m_models.push_back(std::move(model));
    }

}
