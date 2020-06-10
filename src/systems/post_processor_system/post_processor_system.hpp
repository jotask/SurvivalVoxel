#pragma once

#include "systems/system_interface.hpp"
#include "systems/assets_system/texture2D.hpp"
#include "systems/event_system/event.hpp"

#include <glad/glad.h>

namespace aiko
{

    class Shader;
    class ShaderSystem;
    class DisplaySystem;

    class PostProcessorSystem : public System
    {
    public:

        PostProcessorSystem();
        virtual ~PostProcessorSystem() override = default;

        virtual bool connect(SystemConnector&) override;
        virtual bool init() override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

        virtual void beginFrame() override;
        virtual void endFrame() override;

    private:

        void onWindowResize(Event&);

        DisplaySystem* m_displaySystem;
        ShaderSystem* m_shaderSystem;
        Shader* m_shader;

        Texture2D m_texture;

        GLuint m_msfbo;
        GLuint m_fbo;
        GLuint m_rbo;
        GLuint m_vao;

        unsigned int m_width;
        unsigned int m_height;

        bool m_renderEffects;
        bool m_chaos;
        bool m_confuse;
        bool m_shake;


    };

}
