#pragma once

#include "system/system_interface.hpp"
#include "system/light_system/light.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace engine
{

    class ImguiSystem;
    class ShaderSystem;
    class EntityComponentSystem;

    class LightSystem : public System
    {
    public:

        LightSystem();
        virtual ~LightSystem() override = default;

        virtual bool connect(SystemConnector&) override;
        virtual bool init() override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

        void addLight(glm::vec3 position, glm::vec3 color, glm::vec3 diffuse, glm::vec3 ambient, glm::vec3 specular);

    private:

        bool m_renderImgui;

        ImguiSystem* m_imguiSystem;
        ShaderSystem* m_shaderSystem;
        EntityComponentSystem* m_entitySystem;

        std::vector<Light*> m_lights;

    };

}
