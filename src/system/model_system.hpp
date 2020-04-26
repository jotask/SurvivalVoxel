#pragma once

#include "system/system_interface.hpp"
#include "system/model.hpp"
#include "utils/shared.hpp"

#include <map>
#include <string>

namespace engine
{

    class CameraSystem;
    class ShaderSystem;

    class ModelSystem : public System
    {
    public:

        ModelSystem();
        virtual ~ModelSystem() override = default;

        virtual bool init() override;
        virtual bool connect(SystemConnector&) override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

    private:
        std::map<std::string, AikoUPtr<model::Model>> m_models;

        CameraSystem* m_cameraSystem;
        ShaderSystem* m_shaderSystem;

    };

}
