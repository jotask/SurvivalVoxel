#pragma once

#include "systems/system_interface.hpp"
#include "systems/assets_system/model.hpp"
#include "systems/assets_system/asset.hpp"

#include <string>
#include <vector>
#include <map>
#include <optional>

namespace aiko
{

    class ImguiSystem;
    class EntityComponentSystem;
    class ShaderSystem;

    class AssetsSystem : public System
    {
    public:

        AssetsSystem();
        virtual ~AssetsSystem() override = default;

        virtual bool connect(SystemConnector&) override;
        virtual bool init() override;

        virtual void render() override;

        template<class T, class... TArgs>
        T* addAsset(AssetType type, TArgs&&... args)
        {
            T* a(new T(std::forward<TArgs>(args)...));
            AikoUPtr<Asset> ptr { a };
            m_assets[type].emplace_back(std::move(ptr));

            return a;

        }

        auto& getAssets(AssetType type)
        {
            return m_assets[type];
        }

    private:

        ImguiSystem*    m_imguiSystem;
        EntityComponentSystem* m_entityComponentSystem;

        bool m_renderImgui;

        std::map<AssetType, std::vector<AikoUPtr<Asset>>> m_assets;


    };

}
