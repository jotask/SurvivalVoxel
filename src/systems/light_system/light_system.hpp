#pragma once

#include "systems/system_interface.hpp"
#include "systems/light_system/light.hpp"
#include "systems/entity_component_system/entity_types.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace aiko
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

        std::vector<entity::EntityId> m_lights;

    };

}
