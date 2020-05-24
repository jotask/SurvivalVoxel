#pragma once

#include "systems/system_interface.hpp"

namespace aiko
{

    class ImguiSystem;

    class AssetsSystem : public System
    {
    public:

        AssetsSystem();
        virtual ~AssetsSystem() override = default;

        virtual bool connect(SystemConnector&) override;
        virtual bool init() override;

        virtual void render() override;

    private:

        ImguiSystem*    m_imguiSystem;

        bool m_renderImgui;

    };

}
