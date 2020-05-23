#pragma once

#include "systems/system_interface.hpp"

#include <glm/glm.hpp>

namespace engine
{
    class DisplaySystem;
    class ImguiSystem;

    class RenderSystem : public System
    {
    public:

        RenderSystem();
        virtual ~RenderSystem() override = default;

        virtual bool init() override;
        virtual bool connect(SystemConnector&) override;

        virtual void render() override;

        virtual void beginFrame() override;

        void swapBuffers() const;

    private:
        DisplaySystem* m_displaySystem;
        ImguiSystem* m_imguiSystem;

        bool m_renderImgui;
        bool m_drawWireframes;
        glm::vec4 m_bgColor;

    };

}
