#pragma once

#include "systems/system_interface.hpp"
#include "systems/assets_system/texture2D.hpp"
#include "systems/event_system/event.hpp"
#include "systems/post_processor_system/effects/effect.hpp"

#include <glad/glad.h>

#include <vector>

namespace aiko
{

    class Shader;
    class RenderSystem;
    class ShaderSystem;
    class DisplaySystem;

    class PostProcessorSystem : public System
    {
    public:

        PostProcessorSystem();
        virtual ~PostProcessorSystem() override = default;

        virtual bool connect(SystemConnector&) override;
        virtual bool init() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

        virtual void beginFrame() override;
        virtual void endFrame() override;

    private:

        void onWindowResize(Event&);

        RenderSystem* m_renderSystem;
        DisplaySystem* m_displaySystem;
        ShaderSystem* m_shaderSystem;
        Shader* m_shader;

        Texture2D m_texture;

        GLuint m_vao;
        GLuint m_fbo;
        GLuint m_rbo;

        unsigned int m_width;
        unsigned int m_height;

        bool m_renderEffects;

        std::vector<AikoUPtr<postprocessing::Effect>> m_effects;


    };

}
