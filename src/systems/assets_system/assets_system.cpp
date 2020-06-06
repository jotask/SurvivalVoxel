#include "systems/assets_system/assets_system.hpp"

#include "systems/imgui_system.hpp"
#include "systems/entity_component_system/entity_component_system.hpp"
#include "systems/entity_component_system/entity.hpp"
#include "systems/shader_system/shader_system.hpp"
#include "systems/entity_component_system/components/model_component.hpp"
#include "utils/json_loader.hpp"

#include "systems/assets_system/assimp_loader.hpp"

#include <imgui.h>

#include <filesystem>

namespace aiko
{
    AssetsSystem::AssetsSystem()
        : m_imguiSystem(nullptr)
        , m_entityComponentSystem(nullptr)
        , m_renderImgui(false)
    {

    }

    bool AssetsSystem::connect(SystemConnector & connector)
    {
        m_imguiSystem = connector.findSystem<ImguiSystem>();
        m_entityComponentSystem = connector.findSystem<EntityComponentSystem>();
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

                auto opt = loader::assimp::loadModel(this, name, modelFolder + file, shader);

                if (opt != std::nullopt)
                {

                    auto& models = m_assets[AssetType::Model];

                    models.emplace_back(std::make_unique<Model>(opt.value()));

                    auto& e = m_entityComponentSystem->addEntity();
                    auto* tmp = static_cast<Model*>(models[models.size() - 1].get());
                    e.addComponent<ModelComponent>(tmp);

                }

            }

        }
        return true;
    }

    void AssetsSystem::render()
    {
        if (m_renderImgui == true)
        {
            ImGui::Begin("AssetsSystem", &m_renderImgui);
            ImGui::End();
        }
    }

}
