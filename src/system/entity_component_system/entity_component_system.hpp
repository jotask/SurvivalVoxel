#pragma once

#include "system/system_interface.hpp"

#include <vector>

namespace engine
{

    class Component;
    class Entity;
    class ImguiSystem;

    class EntityComponentSystem : public System
    {
    public:

        EntityComponentSystem();
        virtual ~EntityComponentSystem() override = default;

        virtual bool init() override;
        virtual bool connect(SystemConnector&) override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

        void refresh();

        Entity& addEntity();

    private:

        std::vector<AikoUPtr<Entity>> m_entities;

        ImguiSystem* m_imguiSystem;
        bool m_renderImgui;

    };

}
