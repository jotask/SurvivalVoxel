#pragma once

#include "systems/system_interface.hpp"
#include "systems/assets_system/model.hpp"

#include <string>
#include <vector>

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

        void loadModel(const std::string path);

    private:

        ImguiSystem*    m_imguiSystem;
        EntityComponentSystem* m_entityComponentSystem;
        ShaderSystem* m_shaderSystem;

        bool m_renderImgui;

        std::vector<Model> m_models;

    };

}
