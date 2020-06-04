#pragma once

#include "systems/system_interface.hpp"

namespace aiko
{

    class ImguiSystem;

    class AudioSystem : public System
    {
    public:

        AudioSystem();
        virtual ~AudioSystem() override = default;

        virtual bool connect(SystemConnector&) override;
        virtual bool init() override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

    private:

        ImguiSystem* m_imguiSystem;

        bool m_renderImgui;

    };

}
