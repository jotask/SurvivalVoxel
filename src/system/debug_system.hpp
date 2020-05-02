#pragma once

#include "system/system_interface.hpp"

namespace engine
{

    class ImguiSystem;
    class ShaderSystem;

    class DebugSystem : public System
    {
    public:

        DebugSystem();
        virtual ~DebugSystem() override = default;

        virtual bool connect(SystemConnector&) override;
        virtual bool init() override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

        const double getFps() const;

    private:

        bool m_renderImgui;

        ImguiSystem* m_imguiSystem;
        ShaderSystem* m_shaderSystem;

        double m_fps;
        double m_previousTime;
        int m_framCount;

    };

}
