#pragma once

#include "system/system_interface.hpp"

namespace engine
{

    class DisplaySystem;

    class ImguiSystem : public System
    {
    public:

        ImguiSystem();
        virtual ~ImguiSystem() override = default;

        virtual bool connect(SystemConnector&) override;
        virtual bool init() override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

    private:

        bool showDemoWindow;

        DisplaySystem* m_displaySystem;

    };

}
